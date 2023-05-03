public class Entidad {
    private String nombre;
    private int total_donado;

    Entidad(String nombre){
        this.nombre = nombre;
        total_donado = 0;
    }

    public int getTotalDonado(){
        return total_donado;
    }

    public void aniadirDonacion(float cantidad){
        total_donado += cantidad;
    }

    public String getNombre(){
        return nombre;
    }

    public void setDonacion(float cantidad){
        total_donado += cantidad;
    }
}


