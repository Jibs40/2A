package tec;

/**
 * Cette interface fixe/définit/spécifie les services d'un passager
 * qui va être pris en charge par une instance d'Autobus.
 * Elle précise les interactions avec une instance d'Autobus. 
 *
 * <p>
 * Un passager posséde un nom et une destination (un mumero d'arret). 
 * Il possède un comportement à la montée et un comportement à chaque arrêt. 
 * Quand un passager arrive a son arrêt de destination, il sort de l'.
 *
 * <p>
 * Dans un autobus, un passager est forcément soit assis, soit debout. 
 * S'il n'est ni assis, ni debout, il est forcement dehors. 
 * Quand un passager est crée, il est dans la position dehors.
 * 
 * <p>
 * Les méthodes changerEnAssis(), changerEnDebout(), accepterSortie() 
 * modifie la position d'un passager. 
 *
 * <p>
 * Le client déclenche la montée du passager dans un autobus par la méthode
 * monterDans(). 
 * Si l'instance d'Autobus accepte la demande, il déclenche un des 
 * méthodes qui modifient la position du passager.
 *
 * <p>
 * A chaque arrêt, la méthode nouvelArret() est appelée par une instance d'Autobus.
 * Le passager peut choisir de changer de place ou de sortir du bus.
 * Si l'instance d'Autobus accepte la demande, il déclenche un des 
 * méthodes qui modifient la position du passager.
 */
interface Passager {
  /**
   * fournit le nom de du passager.
   */
  public String nom();

  /**
   * Le passager est-il en dehors d'un Autobus ?
   * @return vrai si la position du passager est dehors.
   */
  public boolean estDehors();
  
  /**
   * Le passager est-il assis dans un Autobus ?
   * @return vrai si la position du passager est assis.
   */
  public boolean estAssis();
  
  /**
   * Le passager est-il debout dans un Autobus ?
   * @return vrai si la position du passager est debout.
   */
  public boolean estDebout();
  
  /**
   * Change la position du passager en dehors.
   * Cette méthode est appélee par une instance d'Autobus.
   */
  public void changerEnDehors();
  
  /**
   * Change la position du passager en assis. 
   * Cette méthode est appélee par une instance d'Autobus.
   */
  public void changerEnAssis();
  
  /**
   * Change la position du passager en debout.
   * Cette méthode est appélee par une instance d'Autobus.
   */
  public void changerEnDebout();
  
  /**
   * Cette méthode réalise le caractère à un arrêt du passager. 
   * Elle est appelée par l'instance d'Autobus dans lequel est monté le passager. 
   *
   * @param v l'instance d'Autobus dans lequel se trouve le passager.
   * @param numeroArret numéro de l'arrêt courant.
   */
  public void nouvelArret(Autobus v, int numeroArret);
}

