// módulos http, url, fs, path y socketio
var http = require("http");
var url = require("url");
var fs = require("fs");
var path = require("path");
var socketio = require("socket.io");

function getTimeStamp() {
    return new Date().toISOString();
}


// módulos mongodb y mimeTypes
var MongoClient = require('mongodb').MongoClient;
var MongoServer = require('mongodb').Server;
var mimeTypes = { "html": "text/html", "jpeg": "image/jpeg", "jpg": "image/jpeg", "png": "image/png", "js": "text/javascript", "css": "text/css", "swf": "application/x-shockwave-flash"};

// Server http
var httpServer = http.createServer(
	function(request, response) {
		///
        var uri = url.parse(request.url).pathname;
		if (uri=="/") uri = "/servidor.html";
        ///
		var fname = path.join(process.cwd(), uri);
		fs.exists(fname, function(exists) {
			if (exists) {
				fs.readFile(fname, function(err, data){
					if (!err) {
						var extension = path.extname(fname).split(".")[1];
						var mimeType = mimeTypes[extension];
						response.writeHead(200, mimeType);
						response.write(data);
						response.end();
					}
					else {
						response.writeHead(200, {"Content-Type": "text/plain"});
						response.write('Error de lectura en el fichero: '+uri);
						response.end();
					}
				});
			}
		});		
	}
);


// MongoDB
MongoClient.connect("mongodb://localhost:27017/", { useUnifiedTopology: true }, function(err, db) {
    if(err)
        throw err;

    httpServer.listen(8081);
	var io = socketio(httpServer);

    // la base de datos se llamará domotica
	var dbo = db.db("domotica");


    // Creamos las colecciones de persianas y aire acondicionado
	dbo.createCollection("persianas", function(err, collection){
        if(!err)
            console.log("Coleccion creada en mongo: " + collection.collectionName);
    });

    dbo.createCollection("aire_acondicionado", function(err, collection){
        if(!err)
            console.log("Coleccion creada en mongo: " + collection.collectionName);
    });


    io.sockets.on('connection',function(socket) {
        console.log("Conectado al socket");
    
        // Inserción de colección aire_acondicionado //
        // Insertamos los valores
        socket.on('enviar-datos-aire', function (datos) {
            dbo.collection("aire_acondicionado").insert({valor:datos[0], minimo:datos[1], maximo:datos[2]}, {safe:true},
                function(err, result) {
                    if (!err){
                        console.log("Hemos insertado en A/C: {valor:" + datos[0] + ", minimo:" + datos[1] + ", maximo:" + datos[2] + "}");
                        io.sockets.emit('Registro', getTimeStamp() + " - Modificación de A/C: " + datos[0] + " grados");
                    }
                    else
                        console.log("Error insertando datos en aire acondicionado.");
                });
        });

        // Introducimos el estado (activar el aire acondicionado)
        socket.on('activar_ac', function (datos) {
            dbo.collection("aire_acondicionado").insert({estado:datos}, {safe:true},
                function(err, result) {
                    if (!err){
                        console.log("Insertado estado nuevo de A/C: {estado:" + datos + "}");
                        io.sockets.emit('Registro', getTimeStamp() + " - Aire acondicionado " + datos); // aire acondicionado apagado/encendido
                    }
                    else
                        console.log("Error insertando datos en aire acondicionado.");
                });
        });
    

        // Inserción de colección Persianas //
        // Insertamos los valores
        socket.on('enviar-datos-persianas', function (datos) {
            dbo.collection("persianas").insert({valor:datos[0], minimo:datos[1], maximo:datos[2]}, {safe:true},
                function(err, result) {
                    if (!err){
                        console.log("Insertado en Persianas: {valor:" + datos[0] + ", minimo:" + datos[1] + ", maximo:" + datos[2] + "}");
                        io.sockets.emit('Registro', getTimeStamp() + " - Modificación de luminosidad: " + datos[0]);
                    }
                    else
                        console.log("Error insertando datos en persianas.");
                });
        });

        // Introducimos el estado (activar persiana - abrir persiana)
        socket.on('activar_pers', function (datos) {
            dbo.collection("persianas").insert({estado:datos}, {safe:true},
                function(err, result) {
                    if (!err){
                        console.log("Insertado estado nuevo de las persianas: {estado:" + datos + "}");
                        io.sockets.emit('Registro', getTimeStamp() + " - Persiana " + datos);
                    }
                    else
                        console.log("Error insertando datos en persianas.");
                });
        });

        // Aviso de que se pasa de los umbrales y se cierran las persianas
        socket.on ('aviso', function (sensor) {
            var alarma = "Aviso: " + sensor + " fuera de los umbrales, cerrando persianas"; 
            console.log (alarma);
            io.sockets.emit ('aviso', alarma);
        });

        // Aviso de que se pasa de los umbrales y se cierran las persianas (en caso de que los dos sensores sobrepasen)
        socket.on ('accion', function () {
            var alarma = "Aviso: los sensores fuera de los umbrales, cerrando persianas";
            console.log (alarma);
            io.sockets.emit ('aviso', alarma);
          })

    });

});

console.log("Servicio MongoDB iniciado");

