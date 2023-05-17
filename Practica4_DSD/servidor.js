// módulos http, url, fs, path y socketio
var http = require("http");
var url = require("url");
var fs = require("fs");
var path = require("path");
var socketio = require("socket.io");

// módulos mongodb y mimeTypes
var MongoClient = require('mongodb').MongoClient;
var MongoServer = require('mongodb').Server;
var mimeTypes = { "html": "text/html", "jpeg": "image/jpeg", "jpg": "image/jpeg", "png": "image/png", "js": "text/javascript", "css": "text/css", "swf": "application/x-shockwave-flash"};

// Server http
var httpServer = http.createServer(
	function(request, response) {
		///
        var uri = url.parse(request.url).pathname;
		if (uri=="/") uri = "/domotica.html";
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

httpServer.listen(8080);
console.log("Servicio HTTP iniciado");

// MongoDB
MongoClient.connect("mongodb://localhost:27017/", { useUnifiedTopology: true }, function(err, db) {
    if(err)
        throw err;

    httpServer.listen(8080);
	var io = socketio(httpServer);

    // la base de datos se llamará domotica
	var dbo = db.db("domotica");

    // Creamos las colecciones de persianas y aire acondicionado
	dbo.createCollection("persianas", function(err, collection){
        if(!err)
                console.log("Coleccion creada en Mongo con nombre: " + collection.collectionName);
    });

    dbo.createCollection("aire_acondicionado", function(err, collection){
        if(!err)
                console.log("Coleccion creada en Mongo con nombre: " + collection.collectionName);
    });


    io.sockets.on('connection',function(socket) {
        console.log("Conectado");
    
        /*** Inserción de colección Aire_Acondicionado ***/
          /** Valores **/
        socket.on('enviar-datos-aire', function (datos) {
            dbo.collection("aire_acondicionado").insert({valor:datos[0], minimo:datos[1], maximo:datos[2]}, {safe:true},
                function(err, result) {
                    if (!err) {
                    console.log("Hemos insertado en A/C: {valor:" + datos[0] + ", minimo:" + datos[1] + ", maximo:" + datos[2] + "}");
                    io.sockets.emit('Registro', getTimeStamp() + " - Modificación de A/C ");
                    }
                    else
                        console.log("Error al insertar datos en la colección.");
                });
        });

          /** Estado **/
        socket.on('slider_1', function (datos) {
            dbo.collection("aire_acondicionado").insert({estado:datos}, {safe:true},
                function(err, result) {
                    if (!err) {
                        console.log("Insertado en A/C: {estado:" + datos + "}");
                        io.sockets.emit('Registro', getTimeStamp() + " - Aire acondicionado " + datos);
                    }
                    else
                        console.log("Error al insertar datos en la colección.");
                });
        });
    

        /*** Inserción de colección Persianas ***/
        /** Valores **/
        socket.on('enviar-datos-persianas', function (datos) {
            dbo.collection("persianas").insert({valor:datos[0], minimo:datos[1], maximo:datos[2]}, {safe:true},
                function(err, result) {
                    if (!err) {
                        console.log("Insertado en Persianas: {valor:" + datos[0] + ", minimo:" + datos[1] + ", maximo:" + datos[2] + "}");
                        io.sockets.emit('Registro', getTimeStamp() + " - Modificación persianas");
                    }
                    else
                        console.log("Error al insertar datos en la colección.");
                });
        });

        /** Estado **/
        socket.on('slider_2', function (datos) {
            dbo.collection("persianas").insert({estado:datos}, {safe:true},
                function(err, result) {
                    if (!err) {
                        console.log("Insertado en Persianas: {estado:"+datos+"}");
                        io.sockets.emit('Registro', getTimeStamp() + " - Persianas " + datos);
                    }
                    else
                        console.log("Error al insertar datos en la colección.");
                });
        });

        /*** Avisos ***/
        socket.on ('aviso', function (sensor) {
            var alarma = "Aviso: " + sensor + " fuera de umbral"; // cambiar
            console.log (alarma);
            io.sockets.emit ('aviso', alarma);
        });

        socket.on ('accion', function () {
            var alarma = "Aviso: los sensores sobrepasan los umbrales máximos, abriendo persianas";
            console.log (alarma);
            io.sockets.emit ('aviso', alarma);
        });

    });

});

console.log("Servicio MongoDB iniciado");

