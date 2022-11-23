package tec;

class PassagerStandard
  extends PassagerAbstrait {
  // constructor
  public PassagerStandard(String nom, int destination) {
    super(nom, destination);
  }

  public void monterDans(Autobus t) {
    boolean place_assises = t.aPlaceAssise();
    boolean place_debout = t.aPlaceDebout();
    if(place_assises == true) {
      t.monteeDemanderAssis(this);
    }
    else if(place_debout == true) {
      t.monteeDemanderDebout(this);
    }
  }

  protected void faireChoixArret(Autobus t, int numeroArret) {}
}
