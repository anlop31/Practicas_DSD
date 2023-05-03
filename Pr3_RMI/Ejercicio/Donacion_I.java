import java.rmi.Remote;
import java.rmi.RemoteException;
import java.rmi.NotBoundException;


public interface Donacion_I extends Remote {
    Donacion_I getReplica() throws RemoteException;

    public void registro_cliente(String nombre) throws RemoteException;

    public boolean estaRegistrado(String nombre) throws RemoteException;

    public int getTotalEntidades() throws RemoteException;

    public void donar(String nombre, int cantidad) throws RemoteException, NotBoundException;
    public void recibirActualizacion(int total) throws RemoteException;
    public Entidad getEntidad(String nombre) throws RemoteException;

    public int consultarTotalDonado(String nombre) throws RemoteException, NotBoundException;
    public int consultarTotalDonadoUsuario(String nombre) throws RemoteException;

}