package tec;

public class FabriqueTec {

  public FabriqueTec() {}

  static public Usager fairePassagerStandard(String nom, int destination) {
    Usager p = new PassagerStandard(nom, destination);
    return p;
  }

  static public Usager fairePassagerStresse(String nom, int destination) {
    Usager p = new PassagerStresse(nom, destination);
    return p;
  }

  static public PassagerLunatique fairePassagerLunatique(String nom, int destination) {
    PassagerLunatique p = new PassagerLunatique(nom, destination);
    return p;
  }
}