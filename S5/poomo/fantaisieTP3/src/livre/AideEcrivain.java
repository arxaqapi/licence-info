package livre;

import java.util.Comparator;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.NavigableSet;
import java.util.TreeSet;

import bataille.Bataille;
import bataille.Camp;
import protagoniste.Domaine;
import protagoniste.Heros;
import protagoniste.Homme;
import protagoniste.Monstre;
import protagoniste.ZoneDeCombat;

public class AideEcrivain {
	
	private LinkedList<Homme> listeTriee = new LinkedList<Homme>();
	private TreeSet<Monstre<?>> monstreDomaineSet = 
			new TreeSet<Monstre<?>>(
					new Comparator<Monstre<?>>() {
						public int compare(Monstre<?> arg0, Monstre<?> arg1) {
							Domaine darg0 = arg0.getDomaine();
							Domaine darg1 = arg1.getDomaine();
							// prevent the exclusion of same domain monster
							if (darg0 == darg1 && !arg0.equals(arg1)) {
								return -1;
							}
							return darg0.compareTo(darg1);
						}
					});
	private TreeSet<Monstre<?>> monstresZoneSet = 
			new TreeSet<Monstre<?>>(
					new Comparator <Monstre<?>>() {
						public int compare(Monstre<?> arg0, Monstre<?> arg1) {
							ZoneDeCombat zarg0 = arg0.getZoneDeCombat();
							ZoneDeCombat zarg1 = arg1.getZoneDeCombat();
							int farg0 = arg0.getForceDeVie();
							int farg1 = arg1.getForceDeVie();
							if (zarg0 == zarg1 && farg0 == farg1) {
								return -1;
							} else if (zarg0 == zarg1) {
								if (farg0 > farg1) {
									return -1;
								}
								if (farg0 < farg1) {
									return 1;
								}
							}
							return zarg0.compareTo(zarg1);
						}
					});
	
	private NavigableSet<Monstre<?>> monstresDeFeu; // = monstreDomaineSet.headSet(new Monstre<Feu>(), true);
	private NavigableSet<Monstre<?>> monstresDeGlace; 
	private NavigableSet<Monstre<?>> monstesTranchants;
	
	private Bataille bataille;
	
	public AideEcrivain(Bataille bataille) {
		this.bataille = bataille;
	}
	
	public String visualiserForcesHumaines() {
		Camp<Homme> c = bataille.getCampHumains();
		int iHeros = 0;
		
		for(Homme h: c) {
			if (h instanceof Heros) {
				listeTriee.add(iHeros, h);
				iHeros += 1;
			} else if (h instanceof Homme) {
				listeTriee.add(h);
			}
		}
		
//		for(Homme h: c) {
//			if (h.getForceDeVie() == 100) {
//				listeTriee.add(iHeros, h);
//				iHeros += 1;
//			} else if (h.getForceDeVie() == 70) {
//				listeTriee.add(h);
//			}
//		}
			
		return listeTriee.toString();
	}
	
	public String ordreNaturelMonstre() {
		Camp<Monstre<?>> c = bataille.getCampMonstres();
		
		TreeSet<String> col = new TreeSet<String>();
		
		String final_string = "";
		
		for(Monstre<?> m: c) {
			col.add(m.getNom());
		}
		for(String s: col) {
			final_string += (s + ", ");
		}
		return final_string;
	}
	
	
	public void updateMonstresDomaine() {
		Camp<Monstre<?>> c = bataille.getCampMonstres();
		for(Monstre<?> m: c) {
			monstreDomaineSet.add(m);
		}
	}
	
	public String ordreMonstreDomaine() {
		updateMonstresDomaine();
		String str = "";
		str += "FEU :\n";
		for(Monstre<?> m: monstreDomaineSet) {
			if(m.getDomaine() == Domaine.FEU) {
				str += (m.getNom() + ", ");
			}
		}
		str += "\nGLACE :\n";
		for(Monstre<?> m: monstreDomaineSet) {
			if(m.getDomaine() == Domaine.GLACE) {
				str += m.getNom() + ", ";
			}
		}
		str += "\nTRANCHANT :\n";
		for(Monstre<?> m: monstreDomaineSet) {
			if(m.getDomaine() == Domaine.TRANCHANT) {
				str += m.getNom() + ", ";
			}
		}
		return str;
	}
	
	public void updateMonstresZone() {
		Camp<Monstre<?>> c = bataille.getCampMonstres();
		for(Monstre<?> m: c) {
			monstresZoneSet.add(m);
		}
	}
	
	public String ordreMonstreZone() {
		updateMonstresZone();
		String str = "";
		str += "AERIEN :\n";
		for(Monstre<?> m: monstresZoneSet) {
			if(m.getZoneDeCombat() == ZoneDeCombat.AERIEN) {
				str += (m.getNom() + ": " + m.getForceDeVie() + ", ");
			}
		}
		str += "\nAQUATIQUE :\n";
		for(Monstre<?> m: monstresZoneSet) {
			if(m.getZoneDeCombat() == ZoneDeCombat.AQUATIQUE) {
				str += (m.getNom() + ": " + m.getForceDeVie() + ", ");
			}
		}
		str += "\nTERRESTRE :\n";
		for(Monstre<?> m: monstresZoneSet) {
			if(m.getZoneDeCombat() == ZoneDeCombat.TERRESTRE) {
				str += (m.getNom() + ": " + m.getForceDeVie() + ", ");
			}
		}
		return str;
	}

	public NavigableSet<Monstre<?>> getMonstresDeFeu() {
		return monstresDeFeu;
	}

	public NavigableSet<Monstre<?>> getMonstresDeGlace() {
		return monstresDeGlace;
	}

	public NavigableSet<Monstre<?>> getMonstesTranchants() {
		return monstesTranchants;
	}
	
	public Monstre<?> firstMonstreDomaine(Domaine d) {
		for (Iterator<Monstre<?>> it = monstreDomaineSet.iterator(); it.hasNext();) {
			Monstre<?> m = it.next();
			if (m.getDomaine() == d) {
				return m;
			}
		}
		return null;
	}
	
	public void initMonstresDeFeu() {
		monstresDeFeu = monstreDomaineSet.headSet(firstMonstreDomaine(Domaine.GLACE), false);
	}
	
	
}
