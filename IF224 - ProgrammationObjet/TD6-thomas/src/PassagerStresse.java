package tec;

public class PassagerStresse
  implements Usager, Passager {
  
  private Position position;
  private String nom;
  private int destination;


  // constructor
  public PassagerStresse(String nom, int destination) {
    this.position = new Position();
    this.nom = nom;
    this.destination = destination;
  }

  //methods

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

  public void monterDans(Autobus t) {
    boolean place_assises = t.aPlaceAssise();
    if(place_assises == true) {
      t.monteeDemanderAssis(this);
    }
  }

  public void nouvelArret(Autobus t, int numeroArret) {
    if (((destination - 3) <= numeroArret) && !estDebout())
      changerEnDebout();
    
    if(numeroArret == destination){
      t.arretDemanderSortie(this);
    }
  }


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
