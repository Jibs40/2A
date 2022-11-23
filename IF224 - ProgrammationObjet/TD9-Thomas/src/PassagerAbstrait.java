package tec;

abstract public class PassagerAbstrait
  implements Usager, Passager {
  
  private Position position;
  private String nom;
  private int destination;


  // constructor
  public PassagerAbstrait(String nom, int destination) {
    this.position = new Position();
    this.nom = nom;
    this.destination = destination;
  }

  //methods

  protected int getDestination() {
    return destination;
  }

  public String nom() {
    return this.nom;
  }

  public boolean estDehors() { 
    return position.estDehors();
  }

  public boolean estAssis() {
    return position.estAssis();
  }

  public boolean estDebout() {
    return position.estDebout();
  }

  public void changerEnDehors() {
    position = position.dehors();
  }

  public void changerEnAssis() {
    position = position.assis();
  }

  public void changerEnDebout() {
    position = position.debout();
  }

  public void nouvelArret(Autobus t, int numeroArret) {
    faireChoixArret(t, numeroArret);
    sortirADestination(t, numeroArret);
  }

  protected void sortirADestination(Autobus t, int numeroArret) {
    if(numeroArret == destination){
      t.arretDemanderSortie(this);
    }
  }

  abstract protected void faireChoixArret(Autobus t, int numeroArret);

  public String toString() {
    if(estDehors() == true){
      return nom+" <endehors>"; 
    }else if(estAssis() == true){
      return nom+" <assis>"; 
    }else if(estDebout() == true){
      return nom+" <debout>"; 
    }
  return null;
  }
}
