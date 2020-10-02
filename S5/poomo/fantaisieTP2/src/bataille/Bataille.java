package bataille;

import protagoniste.EtreVivant;
import protagoniste.Homme;
import protagoniste.Monstre;

public class Bataille {
	private Camp<EtreVivant> campHumains;
	private Camp<EtreVivant> campMonstres;
	
	public void ajouter(Homme homme) {
		campHumains.ajouter(homme);
	}
	
	public void eliminer(Homme homme) {
		campHumains.eliminer(homme);
	}
	
	public void ajouter(Monstre monstre) {
		campMonstres.ajouter(monstre);
	}
	
	public void eliminer(Monstre monstre) {
		campHumains.eliminer(monstre);
	}
}
