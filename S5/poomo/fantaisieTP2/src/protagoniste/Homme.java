package protagoniste;

import bataille.Bataille;

public class Homme extends EtreVivant {

	public Homme(String nom) {
		super(nom, 100);
	}
	
	public void rejointBataille(Bataille bataille) {
		
	}
	
	public void mourir() {
		
	}

	@Override
	public String toString() {
		return "Homme [nom=" + nom + ", forceDeVie=" + forceDeVie + "]";
	}
	
	
	
}
