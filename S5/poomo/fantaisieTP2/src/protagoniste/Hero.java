package protagoniste;

public class Hero extends Homme{

	public Hero(String nom) {
		super(nom);
	}

	@Override
	public String toString() {
		return "Hero [nom=" + nom + ", forceDeVie=" + forceDeVie + "]";
	}

}
