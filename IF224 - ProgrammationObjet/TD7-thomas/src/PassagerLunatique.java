package tec;

public class PassagerLunatique
  implements Usager, Passager {

  private Position position;
  private String nom;
  private int destination;


  // constructor
  public PassagerLunatique(String nom, int destination) {
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
    boolean place_debout = t.aPlaceDebout();
    if(place_assises == true){
      t.monteeDemanderAssis(this);
    }
    else if(place_debout == true){
      t.monteeDemanderDebout(this);
    }
  }

  public void nouvelArret(Autobus t, int numeroArret) {
    
    if(numeroArret == destination) {
      t.arretDemanderSortie(this);
    }
    else if(estAssis() && t.aPlaceDebout()) {
      t.arretDemanderDebout(this);
    }
    else if(estDebout() && t.aPlaceAssise()) {
      t.arretDemanderAssis(this);
    }
  }


  public String toString() {
    if(this.estDehors() == true){
      return nom+" <endehors>"; 
    }else if(this.estAssis() == true){
      return nom+" <assis>"; 
    }else if(this.estDebout() == true){
      return nom+" <debout>"; 
    }
  return null;
  }

}
