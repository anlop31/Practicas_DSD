import java.net.MalformedURLException;
import java.rmi.*;
import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;
import java.rmi.server.*;

//import contador.contador;
public class Servidor1 {
    public static void main(String[] args) {
        // Crea e instala el gestor de seguridad
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            // Crea una instancia de contador
            // System.setProperty("java.rmi.server.hostname","192.168.1.107");
            String nombre1 = "servidor2";
            Registry reg = LocateRegistry.createRegistry(1098);
            Donacion miDonacion = new Donacion(nombre1);
            Naming.rebind("servidor1", miDonacion);

            System.out.println("Servidor RemoteException | MalformedURLExceptiondor preparado");
        } catch (RemoteException | MalformedURLException e) {
            System.out.println("Exception: " + e.getMessage());
        }
    }
}