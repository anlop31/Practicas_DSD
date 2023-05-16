import java.net.MalformedURLException;
import java.rmi.registry.LocateRegistry;
import java.rmi.*;
import java.rmi.registry.Registry;


public class Cliente {
    public static void main(String[] args) {
        // Crea e instala el gestor de seguridad
        if (System.getSecurityManager() == null) {
            System.setSecurityManager(new SecurityManager());
        }
        try {
            // Crea el stub para el cliente especificando el nombre del servidor
            // Registry mireg = LocateRegistry.getRegistry("127.0.0.1", 1097);
            Registry mireg = LocateRegistry.getRegistry("127.0.0.1", 1098);

            System.out.println("Registros creados");
            System.out.println("Buscando servidores de donacion...");

            Donacion_I midonacion1 = (Donacion_I) mireg.lookup("servidor1");
            Donacion_I midonacion2 = (Donacion_I) mireg.lookup("servidor2");
            System.out.println("servidores encontrados");


            // registramos
            midonacion1.registro_cliente("Paco");
            midonacion2.registro_cliente("Paco");
            midonacion1.registro_cliente("Juan");
            midonacion2.registro_cliente("Pepe");

            // donar
            midonacion1.donar("Pepe", 200);
            midonacion2.donar("Paco", 100);
            midonacion1.donar("Juan", 70);

        } catch (NotBoundException | RemoteException e) {
            System.err.println("Exception del sistema: " + e);
        }
        System.exit(0);
    }
}