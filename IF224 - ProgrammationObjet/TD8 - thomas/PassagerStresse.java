//source without documentation for javadoc
package tec;

import javax.print.attribute.standard.Destination;
import javax.swing.JSpinner.NumberEditor;

import tec.PassagerStandard;

class PassagerStresse
  extends PassagerStandard {

  // constructor
  public PassagerStresse(String nom, int destination) {
    super(nom, destination);
  }

  //methods

  @Override
  public void monterDans(Autobus t) {
    boolean place_assises = t.aPlaceAssise();
    if(place_assises == true) {
      t.monteeDemanderAssis(this);
      changerEnAssis();
    }
  }

  @Override
  public void nouvelArret(Autobus t, int numeroArret) {
    if (((getDestination() - 3) <= numeroArret) && !estDebout())
      t.arretDemanderDebout(this);
    
    super.nouvelArret(t, numeroArret);
  }
}
