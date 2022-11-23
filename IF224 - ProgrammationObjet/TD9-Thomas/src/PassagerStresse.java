package tec;

class PassagerStresse
  extends PassagerAbstrait {

  // constructor
  public PassagerStresse(String nom, int destination) {
    super(nom, destination);
  }

  //methods
  public void monterDans(Autobus t) {
    boolean place_assises = t.aPlaceAssise();
    if(place_assises == true) {
      t.monteeDemanderAssis(this);
    }
  }

  protected void faireChoixArret(Autobus t, int numeroArret) {
    if (((getDestination() - 3) <= numeroArret) && !estDebout())
      t.arretDemanderDebout(this);
  }
}
