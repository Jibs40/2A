//source without documentation for javadoc
package tec;
import java.util.ArrayList;

public class Autobus {

  private int numeroArret = 0;

  private Jauge assis;
  private Jauge debout;
  private ArrayList <Passager> passagers;
  private ArrayList <Passager> passagersToRemove;

  // constructor
  public Autobus(int nbPlaceAssise, int nbPlaceDebout) {
    assis = new Jauge(nbPlaceAssise, 0);
    debout = new Jauge(nbPlaceDebout, 0);
    passagers = new ArrayList<Passager>(nbPlaceAssise + nbPlaceDebout);
    passagersToRemove = new ArrayList<Passager>(nbPlaceAssise + nbPlaceDebout);
  }

  //methods
  boolean aPlaceAssise() {
    return assis.estVert();
  }

  boolean aPlaceDebout() {
    return debout.estVert();
  }

  void monteeDemanderAssis(Passager p) {
    assis.incrementer();
    passagers.add(p);
    p.changerEnAssis();
  }

  void monteeDemanderDebout(Passager p) {
    debout.incrementer();
    passagers.add(p);
    p.changerEnDebout();
  }

  public void allerArretSuivant() {
    numeroArret++;
    for (Passager p : passagers) {
      p.nouvelArret(this, numeroArret);
    }
    passagers.removeAll(passagersToRemove);
    passagersToRemove.clear();
  }

  void arretDemanderAssis(Passager p) {
    assis.incrementer();
    debout.decrementer();
    p.changerEnAssis();
  }

  void arretDemanderDebout(Passager p) {
    assis.decrementer();
    debout.incrementer();
    p.changerEnDebout();
  }

  void arretDemanderSortie(Passager p) {
    if (p.estAssis()) {
      assis.decrementer();
    }else if (p.estDebout()) {
      debout.decrementer();
    }
    //passagers.remove(p);
    passagersToRemove.add(p);
    //passagers.set(passagers.indexOf(p), null);
    p.changerEnDehors();
  }

  public String toString() {
    
    return "[arret:" + numeroArret + ", assis:" + assis.toString() + ", debout:" + debout.toString() + "]"; 
  }
}
