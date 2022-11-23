package tec;

public class PassagerLunatique
  extends PassagerAbstrait {
  // constructor
  public PassagerLunatique(String nom, int destination) {
    super(nom, destination);
  }

  //methods
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

  protected void faireChoixArret(Autobus t, int numeroArret) {
    if(estAssis() && t.aPlaceDebout()) {
      t.arretDemanderDebout(this);
    }
    else if(estDebout() && t.aPlaceAssise()) {
      t.arretDemanderAssis(this);
    }
  }
}
