import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.UnicastRemoteObject;
import java.net.MalformedURLException;
import java.rmi.NotBoundException;


import java.util.ArrayList;

public class Donacion extends UnicastRemoteObject implements Donacion_I {
    private int subtotal_donado;
    int total_donado;
    ArrayList<Entidad> entidades;
    String nombreReplica;


    public Donacion(String nombreServer) throws RemoteException {
        entidades = new ArrayList<Entidad>();
        nombreReplica = nombreServer;
    }

    public Donacion_I getReplica() throws RemoteException, NotBoundException {
        Registry reg;
        if(nombreReplica == "servidor1")
            reg = LocateRegistry.getRegistry("127.0.0.1", 1097);
        else 
            reg = LocateRegistry.getRegistry("127.0.0.1", 1098);


        return (Donacion_I) reg.lookup(nombreReplica);
    }

    public void registro_cliente(String nombre) throws RemoteException, NotBoundException{
        Donacion_I replica = this.getReplica();
        boolean esta_registrado = this.estaRegistrado(nombre);
        boolean esta_registrado_en_replica = replica.estaRegistrado(nombre);

        if(esta_registrado || esta_registrado_en_replica){
            System.out.println(nombre + " ya registrado en el sistema.");
        }
        else{ // no registrado
            int entidades_replica = replica.getTotalEntidades();

            if(entidades.size() <= entidades_replica){
                System.out.println("Registrado a "+nombre);
                Entidad entidad = new Entidad(nombre);
                entidades.add(entidad);
            }
            else{
                System.out.println("Se registra la entidad "+nombre+" en la replica");
                replica.registro_cliente(nombre);
            }
        }

    }

    public boolean estaRegistrado(String nombre) throws RemoteException{
        boolean registrado = false;

        for(int i=0; i<entidades.size(); i++){
            if(entidades.get(i).getNombre() == nombre)
            registrado = true;
        }

        return registrado;
    }

    public int getTotalEntidades() throws RemoteException{
        return entidades.size();
    }

    public void donar(String nombre, int cantidad) throws RemoteException, NotBoundException {
        // if(estaRegistrado(nombre))
        //     subtotal_donado += cantidad;

        Donacion_I replica = this.getReplica();

        if(cantidad > 0){
            Entidad entidad = null;
            entidad = this.getEntidad(nombre);
            subtotal_donado += cantidad;

            System.out.println("Donado "+cantidad+" a la cantidad actual de: "+total_donado);
            total_donado = total_donado + cantidad;

            replica.recibirActualizacion(total_donado);
        }

        

    }

    public void recibirActualizacion(int total) throws RemoteException{
        total_donado = total;
    }

    public Entidad getEntidad(String nombre) throws RemoteException{
        Entidad entidad = new Entidad("nombre");

        if(estaRegistrado(nombre))
            for(int i=0; i<entidades.size(); i++){
                if(entidades.get(i).getNombre() == nombre)
                    entidad = entidades.get(i);
            }

        return entidad;
    }

    public int consultarSubtotalDonado(String nombre) throws RemoteException{
        if(this.getEntidad(nombre).getTotalDonado() > 0){
            return subtotal_donado;
        }
        else{
            return -1;
        }
    }


    public int consultarTotalDonado(String nombre) throws RemoteException, NotBoundException{
        if(this.getEntidad(nombre).getTotalDonado() > 0){
            return total_donado;
        }
        else{
            return -1;
        }
    }


    public int consultarTotalDonadoUsuario(String nombre) throws RemoteException{
        int cantidad = this.getEntidad(nombre).getTotalDonado();

        return cantidad;
    }

}

