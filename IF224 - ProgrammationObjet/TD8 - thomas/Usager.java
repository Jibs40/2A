package tec;

public interface Usager {
  /**
   * Cette méthode réalise le caractère à la montée du passager.
   * Elle est appelée par le client.
   *
   * @param v l'instance d'Autobus dans lequel va monter le passager.
   */
  public void monterDans(Autobus v);

  /**
   * fournit le nom de du passager.
   */
  public String nom();
}
