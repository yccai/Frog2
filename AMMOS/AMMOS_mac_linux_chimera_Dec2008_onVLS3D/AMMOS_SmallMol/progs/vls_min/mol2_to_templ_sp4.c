///////////////////////////////////////////////////
///                                             ///
///                 AMMOS_SmallMol              ///
///          written by T. Pencheva, M.Miteva   ///
///                 2007-2008                   ///
///                                             ///
///////////////////////////////////////////////////


// -------------------------------------------------------------------------------------
// Download data from *.mol2 format in order to be created template and input_ligand.pdb


#include <stdio.h>	// Allows the program to interact with the screen, keyboard and filesystem of your computer.	
#include <string.h>	// For concatenation of two strings 
#include <stdlib.h>
#include <ctype.h>	// For convertion of upper to lower case 

#define max_numb_atoms 1000
#define max_numb_bonds 1000
#define max_name_len 10

typedef struct 
{
	int 	number [max_numb_atoms],	// Counter for numbers of atoms
		countbonds [max_numb_atoms],	// Counter for numbers of bonds
		bonds [max_numb_atoms][10];	// Array for numbers of atoms connected with the current atom

	float	coordx [max_numb_atoms], 	// Atoms coordinates  
		coordy [max_numb_atoms], 	// Atoms coordinates  
		coordz [max_numb_atoms], 	// Atoms coordinates  
		charge [max_numb_atoms], 	// Atoms charge  
		bondtypes [max_numb_atoms][10];	// Array for types of bonds connected with the current atom
	
	char	*name [max_numb_atoms],	// Name of the atom 
                *namech [max_numb_atoms], // Name of the atomch  
		*type [max_numb_atoms],	// Type of the atom - column 1  
		type2 [max_name_len],	// Type of the atom - column 2  
		type3 [max_name_len];	// Type of the atom - column 3
} ATOM;

typedef struct 
{
	int 	origin [max_numb_bonds],	// Number of the first atom in the bond 
		target [max_numb_bonds];	// Number of the second atom in the bond  		
		
	char 	*type [max_numb_bonds];		// Type of the bond  
} BOND;


// Function lower converts characters in string a to lower case
void lower (char *str, int len)
{
	int i;
	for (i = 0; i < len; i++) str [i] = tolower (str[i]); 
}


// Function rmchr removes a character from a string
// Will be used to remove a point in the atom type
void rmchr (char a[], char c)   // Remove 'c' from the string 'a'
{
     char temp [10];         	// Temporary array
     char *ptr = a;           	// Pointer to traverse array
     char *tptr = temp;     	// Pointer for the temp array
     
     while (*ptr != '\0')
     {
        if (*ptr != c)
        {
           *tptr = *ptr;
           tptr++;
        }
        ptr++;
     }
     *tptr = '\0';
     strcpy (a, temp);     
}

main()
{

int	i = 0, j = 0, k = 0, l = 0, n = 0, c = 0, h = 0, 
	a = 0, b = 0, d = 0, e = 0, f = 0, p = 0, q = 0, 
	r = 0, s = 0, t = 0, 	// Counters  
	flag = 0,		// Flag for corresponding atom types
	write_warn = 0,		// Count the number of warnings
	count_amid = 0,		
	count_gua = 0,		
	point_cam [1000],	
	point_nam [1000],	
	point_oam [1000],	
	point_cgua [1000],	
	point_ngua [1000][3],	
	point_nplan [1000],	// Keep number of N atoms with type N.pl3 
	point_n2 [1000],	// Keep number of N atoms with type N.2 
	line_length = 1000, 	// Length of the line  
	atoms_number,  		// Number of atoms  
        bonds_number, 		// Number of bonds
        ll = 0,
        len = 0,
        nb = 0; //nb=atom.name [i] 

char	buffer [line_length],		// Buffer with line_length number of chars - max width of one row  
					// Define string sufficiently large to store a line of input  
	*rule_0 [max_numb_atoms],	  
	*rule_1 [max_numb_atoms],	  
	*rule_2 [max_numb_atoms],	  
	*rule_3 [max_numb_atoms],	  
	*rule_4 [max_numb_atoms],	  
	*rule_5 [max_numb_atoms],	  
	*rule_6 [max_numb_atoms],	// For N.pl3 type  
	*rule_7 [max_numb_atoms];	// For N.2 type  
		
ATOM atom;
BOND bond;


// Initialization of pointers for atoms names and types and for bonds types
for (i = 0; i < max_numb_atoms; i++) 
{
	atom.name [i] = (char *) malloc (max_name_len);
	atom.namech [i] = (char *) malloc (max_name_len);
	atom.type [i] = (char *) malloc (max_name_len);
	rule_0 [i] = (char *) malloc (line_length);
	rule_1 [i] = (char *) malloc (line_length);
	rule_2 [i] = (char *) malloc (line_length);
	rule_3 [i] = (char *) malloc (line_length);
	rule_4 [i] = (char *) malloc (line_length);
	rule_5 [i] = (char *) malloc (line_length);
	rule_6 [i] = (char *) malloc (line_length);
	rule_7 [i] = (char *) malloc (line_length);
}

for (j = 0; j < max_numb_bonds; j++) 
{
	bond.type [j] = (char *) malloc (max_name_len);
}


FILE 	*mol2, *mol, *pdb, *warn, *fopen(); 

// Open working files for reading and writting  
	mol2 = fopen ("input.mol2", "r");   
	mol = fopen ("mol", "w" );
	pdb = fopen ("input_ligand.pdb", "w" );
	warn = fopen ("warning", "w" );

// Reading from *.mol2 file  
	fgets (buffer, line_length, mol2);	
	while (strncmp (buffer, "@<TRIPOS>MOLECULE", 17) != 0 ) fgets (buffer, line_length, mol2);

// Reading the name of the molecule  
	fgets (buffer, line_length, mol2);
	fprintf (warn, "%s", buffer);

// Reading atoms and bonds numbers 
	fgets (buffer, line_length, mol2);
	sscanf (buffer, "%i %i", &atoms_number, &bonds_number);	

// Reading data for atoms  
	fgets (buffer, line_length, mol2);	
	while (strncmp (buffer, "@<TRIPOS>ATOM", 13) != 0 ) fgets (buffer, line_length, mol2);

	fprintf (mol, "%i\n", atoms_number);
	for (i = 0; i < atoms_number; i++)
	{
		fgets (buffer, line_length, mol2); 
		sscanf (buffer, "%i %s %f %f %f %s %s %s %f", &atom.number [i], atom.name [i], 
			&atom.coordx [i], &atom.coordy [i], &atom.coordz [i], 
			atom.type [i], atom.type2, atom.type3, &atom.charge [i]);	
              


//	if(strlen(atom.name [i])>0{
//		len = strlen(atom.name [i]);
//		sscanf(atom.name [i]+len-1, "%i", &ll);
//		if(ll < 0 || ll > 9)
		
		    
//			write_warn = 1;
//			fprintf (warn, "%s %s\n", "atom.name  ", atom.name [i]);
//			sprintf(atom.name [i]+strlen(atom.name [i]), "%i",  nb);				
//			strcpy (atom.name [i], "a");
			
			*(atom.name [i] + 1) = '\0';
			
			sprintf(atom.name [i]+strlen(atom.name [i]), "%i",  i);
//			fprintf (warn, "%s %s\n", "atom.namech  ", atom.name [i]);
//	}
	


		       			
// Corresponding atoms types
// Check for unknown atom type
		if (strcmp (atom.type [i], "H") != 0 && strcmp (atom.type [i], "C.3") != 0 &&
		    strcmp (atom.type [i], "C.2") != 0 && strcmp (atom.type [i], "C.1") != 0 &&	
		    strcmp (atom.type [i], "C.ar") != 0 && strcmp (atom.type [i], "C.cat") != 0 &&
		    strcmp (atom.type [i], "N.4") != 0 && strcmp (atom.type [i], "N.3") != 0 &&
		    strcmp (atom.type [i], "N.2") != 0 && strcmp (atom.type [i], "N.pl3") != 0 && 
		    strcmp (atom.type [i], "N.am") != 0 && strcmp (atom.type [i], "N.ar") != 0 &&
		    strcmp (atom.type [i], "N.1") != 0 && strcmp (atom.type [i], "O.3") != 0 &&
		    strcmp (atom.type [i], "O.2") != 0 && strcmp (atom.type [i], "O.co2") != 0 &&
		    strcmp (atom.type [i], "S.3") != 0 && strcmp (atom.type [i], "S.2") != 0 && 
		    strcmp (atom.type [i], "S.o2") != 0 && strcmp (atom.type [i], "S.o") != 0 &&
		    strcmp (atom.type [i], "S.O2") != 0 && strcmp (atom.type [i], "S.O") != 0 && 
		    strcmp (atom.type [i], "P.3") != 0 && strcmp (atom.type [i], "F") != 0 && 
		    strcmp (atom.type [i], "Br") != 0 && strcmp (atom.type [i], "Cl") != 0 && 
		    strcmp (atom.type [i], "I") != 0 && strcmp (atom.type [i], "K") != 0 && 
		    strcmp (atom.type [i], "Na") != 0 && strcmp (atom.type [i], "Mg") != 0 && 
		    strcmp (atom.type [i], "Ca") != 0 && strcmp (atom.type [i], "Zn") != 0 && 
		    strcmp (atom.type [i], "Fe") != 0) 
		{
			fprintf (warn, "%s %s\n", "Warning: Unknown atom type", atom.type [i]);
			write_warn = 1;
			strcpy (atom.type [i], "dummy");
		}


//Check atom names 
		if (strcmp (atom.name [i], "H") == 0)
                {
                       fprintf (warn, "%s %s\n", "Warning: Unknown atom name", atom.name [i]);
                        write_warn = 1;
//                      strcpy (atom.name [i], "dummy");
                }
//

		if (strcmp (atom.type [i], "H") == 0) strcpy (atom.type [i], "h"); 
		if (strcmp (atom.type [i], "C.3") == 0) strcpy (atom.type [i], "c3"); 
		if (strcmp (atom.type [i], "C.2") == 0) strcpy (atom.type [i], "c2");
		if (strcmp (atom.type [i], "C.1") == 0) strcpy (atom.type [i], "c1");
		if (strcmp (atom.type [i], "C.ar") == 0) strcpy (atom.type [i], "ca");
		if (strcmp (atom.type [i], "C.cat") == 0) strcpy (atom.type [i], "c2");
		if (strcmp (atom.type [i], "N.4") == 0) strcpy (atom.type [i], "n3"); 
		if (strcmp (atom.type [i], "N.3") == 0) strcpy (atom.type [i], "n3"); 
		if (strcmp (atom.type [i], "N.2") == 0) {strcpy (atom.type [i], "n2"); 
							   point_n2 [f] = atom.number [i]; f++;}
		if (strcmp (atom.type [i], "N.pl3") == 0) {strcpy (atom.type [i], "np");  
							   point_nplan [e] = atom.number [i]; e++;}	
		if (strcmp (atom.type [i], "N.am") == 0) strcpy (atom.type [i], "nm");
		if (strcmp (atom.type [i], "N.ar") == 0) strcpy (atom.type [i], "nr"); 
		if (strcmp (atom.type [i], "N.1") == 0) strcpy (atom.type [i], "n1"); 
		if (strcmp (atom.type [i], "O.3") == 0) strcpy (atom.type [i], "o3"); 
		if (strcmp (atom.type [i], "O.2") == 0) strcpy (atom.type [i], "o2"); 
		if (strcmp (atom.type [i], "O.co2") == 0) strcpy (atom.type [i], "o2");
		if (strcmp (atom.type [i], "S.3") == 0) strcpy (atom.type [i], "s32");
		if (strcmp (atom.type [i], "S.2") == 0) strcpy (atom.type [i], "s2");
		if (strcmp (atom.type [i], "S.O2") == 0) strcpy (atom.type [i], "s34");
		if (strcmp (atom.type [i], "S.O") == 0) strcpy (atom.type [i], "s34");		
		if (strcmp (atom.type [i], "S.o2") == 0) strcpy (atom.type [i], "s34");
		if (strcmp (atom.type [i], "S.o") == 0) strcpy (atom.type [i], "s34");
		if (strcmp (atom.type [i], "P.3") == 0) strcpy (atom.type [i], "p35");
		if (strcmp (atom.type [i], "F") == 0) strcpy (atom.type [i], "f"); 
		if (strcmp (atom.type [i], "Br") == 0) strcpy (atom.type [i], "br");
		if (strcmp (atom.type [i], "Cl") == 0) strcpy (atom.type [i], "cl");
		if (strcmp (atom.type [i], "I") == 0) strcpy (atom.type [i], "i");
		if (strcmp (atom.type [i], "K") == 0) strcpy (atom.type [i], "k");
		if (strcmp (atom.type [i], "Na") == 0) strcpy (atom.type [i], "na");
		if (strcmp (atom.type [i], "Mg") == 0) strcpy (atom.type [i], "mg");
		if (strcmp (atom.type [i], "Ca") == 0) strcpy (atom.type [i], "calcium"); 
		if (strcmp (atom.type [i], "Zn") == 0) strcpy (atom.type [i], "zn");
		if (strcmp (atom.type [i], "Fe") == 0) strcpy (atom.type [i], "fe2");
		

// Writing information about atoms in *.pdb file  
		fprintf (pdb, "%s%7i%5s%4s%6s%12.3f%8.3f%8.3f%6s%6s\n", "ATOM", i+1, 
			 atom.name [i], "mol", "0", atom.coordx [i], atom.coordy [i], atom.coordz [i], "1.00", "10.00");

		lower (atom.name [i], 10); 	// Will be used in bonds
		lower (atom.type [i], 10); 	
		rmchr (atom.type [i], '.'); 	// Remove point from string type1


// Writing information about atoms in *.mol file 
//              MODIFICATION P. TUFFERY M . MITEVA 2010 POUR OTER LES CHARGES
//              fprintf (mol, "%s %s%s %s %s %s %5.3f\n", "name", "mol.", atom.name [i], 
//			 "type", atom.type [i], "charge", atom.charge [i]);
                fprintf (mol, "%s %s%s %s %s %s %5.3f\n", "name", "mol.", atom.name [i], 
			 "type", atom.type [i], "charge", 0.);

	}
fprintf (pdb, "%s", "END"); 	


// Reading data for bonds   
	fgets (buffer, line_length, mol2);	// One row should be jumped - it contains @<TRIPOS>BOND  
	fprintf (mol, "%i\n", bonds_number);
	for (j = 0; j < bonds_number; j++)
	{
		fgets (buffer, line_length, mol2);
		sscanf (buffer, "%i %i %i %s", &l, &bond.origin [j], &bond.target[j], bond.type [j]);	


// Equvalent numbers to bonds types
		if (strcmp (bond.type [j], "ar") == 0) strcpy (bond.type [j], "1.5");	// Aromatic bond is equal to 1.5
		if (strcmp (bond.type [j], "am") == 0) 
		{
			strcpy (bond.type [j], "1.25");	
	
			if (strchr (atom.name [bond.origin [j] - 1], 'n' ) && strchr (atom.name [bond.target [j] - 1], 'c' )) 
			{
				point_nam [count_amid] = bond.origin [j];
				point_cam [count_amid] = bond.target [j];
				count_amid ++;
			}
			if (strchr (atom.name [bond.target [j] - 1], 'n' ) && strchr (atom.name [bond.origin [j] - 1], 'c' )) 
			{
				point_nam [count_amid] = bond.target [j];
				point_cam [count_amid] = bond.origin [j];
				count_amid ++;
			}
			else continue;
		}
	}

	for (j = 0; j < bonds_number; j++)
	{
		for (l = 0; l < count_amid; l++)

		// Check for C and O atoms 
		if (bond.origin [j] == point_cam [l] & strcmp (atom.type [bond.target [j] - 1], "o2") == 0) 
		{
			strcpy (bond.type [j], "1.75");
			point_oam [l] = bond.target [j];
		}
		else if (bond.target [j] == point_cam [l] & strcmp (atom.type [bond.origin [j] - 1], "o2") == 0) 
		{
			strcpy (bond.type [j], "1.75");
			point_oam [l] = bond.origin [j];
		}
	}


// Accumulation of all information in the ATOM structure
for (i = 0; i < atoms_number; i++)
{
	for (j = 0; i < 10; i++)
	atom.bonds [i][j] = 0;		// Initialization of the array with 0
	atom.bondtypes [i][j] = 0;	// Initialization of the array with 0
}


for (i = 0; i < atoms_number; i++)
{
	n = 0;		 		// Initialization of bonds counter
	atom.number [i] = i + 1;	// Counter for numbers of atoms	
	
	for (j = 0; j < bonds_number; j++)
	{
		if (bond.origin [j] == atom.number [i])
		{
			atom.bonds [i][n] = bond.target [j]; 		// Array for atoms connected with the current atom
			atom.bondtypes [i][n] = atof (bond.type [j]); 	// Types of bonds connected with the current atom	
			n++;
		}

		if (bond.target [j] == atom.number [i])
		{
			atom.bonds [i][n] = bond.origin [j]; 		// Array for atoms connected with the current atom
			atom.bondtypes [i][n] = atof (bond.type [j]); 	// Types of bonds connected with the current atom
			n++;
		}
	}
	atom.countbonds [i] = n;	// Counter for numbers of bonds
}




// Check for amide-type bond
// Creation of first hybrid-type rule for amide-type bond - C, N, O and H to be in one plane

for (l = 0; l < count_amid; l++)
{
	for (n = 0; n < 3; n++)
	
//Corrected to work for all amides not only with NH	if (strcmp (atom.type [atom.bonds [point_nam [l] - 1][n] - 1], "h") != 0 ) continue;
//Corrected to work for all amides not only with NH	else

	{
		if (point_cam [l] == 0 || atom.bonds [point_cam [l] - 1][0] == 0 || atom.bonds [point_cam [l] - 1][1] == 0 
		    || atom.bonds [point_cam [l] - 1][2] == 0) continue;
		else
		{
			strcat (rule_0 [l], "mol.");
			strcat (rule_0 [l], atom.name [point_cam [l] - 1]);
			strcat (rule_0 [l], " mol.");
			strcat (rule_0 [l], atom.name [atom.bonds [point_cam [l]-1][0] - 1]);
			strcat (rule_0 [l], " mol.");
			strcat (rule_0 [l], atom.name [atom.bonds [point_cam [l]-1][1] - 1]);
			strcat (rule_0 [l], " mol.");
			strcat (rule_0 [l], atom.name [atom.bonds [point_cam [l]-1][2] - 1]);
			strcat (rule_0 [l], " 150 0\n");	
			t ++;
		}

		if (point_cam [l] == 0 || point_oam [l] == 0 || point_nam [l] == 0 || atom.bonds [point_nam [l] - 1][n] == 0) continue;
		else
		{	
			strcat (rule_1 [l], "mol.");
			strcat (rule_1 [l], atom.name [point_cam [l] - 1]);
			strcat (rule_1 [l], " mol.");
			strcat (rule_1 [l], atom.name [point_oam [l] - 1]);
			strcat (rule_1 [l], " mol.");
			strcat (rule_1 [l], atom.name [point_nam [l] - 1]);
			strcat (rule_1 [l], " mol.");
			
//Corrected to work for all amides not only with NH			strcat (rule_1 [l], atom.name [atom.bonds [point_nam [l] - 1][n] - 1]);
			strcat (rule_1 [l], atom.name [atom.bonds [point_nam [l] - 1][1] - 1]);

			strcat (rule_1 [l], " 150 0\n");				
			r ++;
			break;
		}

	}
}


// Creation of second hybrid-type rule for amide-type bond - N.am and all connected atoms to be in one plane
for (l = 0; l < count_amid; l++)
if (point_nam [l] == 0 || atom.bonds [point_nam [l] - 1][0] == 0 || atom.bonds [point_nam [l] - 1][1] == 0 
    || atom.bonds [point_nam [l] - 1][2] == 0) continue;
else
{
		strcat (rule_2 [l], "mol.");
		strcat (rule_2 [l], atom.name [point_nam [l] - 1]);
		strcat (rule_2 [l], " mol.");
		strcat (rule_2 [l], atom.name [atom.bonds [point_nam [l]-1][0] - 1]);
		strcat (rule_2 [l], " mol.");
		strcat (rule_2 [l], atom.name [atom.bonds [point_nam [l]-1][1] - 1]);
		strcat (rule_2 [l], " mol.");
		strcat (rule_2 [l], atom.name [atom.bonds [point_nam [l]-1][2] - 1]);
		strcat (rule_2 [l], " 150 0\n");	
		s ++;
}



//  atoms in guani-type bond
for (i = 0; i < atoms_number; i++)
{
	if (strcmp (atom.type [i], "c2") == 0 & 
	    atom.countbonds [i] == 3 &
	    strcmp (atom.type [atom.bonds [i][0] - 1], "np") == 0 & 
	    strcmp (atom.type [atom.bonds [i][1] - 1], "np") == 0 & 
	    strcmp (atom.type [atom.bonds [i][2] - 1], "np") == 0 )
	{
		point_ngua [count_gua][0] = atom.bonds [i][0];
		point_ngua [count_gua][1] = atom.bonds [i][1];
		point_ngua [count_gua][2] = atom.bonds [i][2];
		point_cgua [count_gua] = atom.number [i];
		count_gua++;
	} 
}

// Formation of the third, fourth and fifth rules 
for (l = 0; l < count_gua; l++)
{ 	
	a = 0; b = 0; d = 0;	// Initialization of counters

	if (point_ngua [l][0] == 0 || point_cgua [l] == 0 || point_ngua [l][1] == 0 || 
	    atom.bonds [point_ngua [l][1] - 1][0] == 0 || 
	    atom.bonds [point_ngua [l][1] - 1][1] == 0 || 
	    atom.bonds [point_ngua [l][1] - 1][2] == 0) continue;

	if (a == 0)
	{	
		strcat (rule_3 [l], "mol.");
		strcat (rule_3 [l], atom.name [point_ngua [l][0] - 1]);
		strcat (rule_3 [l], " mol.");
		strcat (rule_3 [l], atom.name [point_cgua [l] - 1]);
		strcat (rule_3 [l], " mol.");
		strcat (rule_3 [l], atom.name [point_ngua [l][1] - 1]);
		strcat (rule_3 [l], " mol.");
		for (n = 0; n < 3; n++)
		{
			if (atom.bonds [point_ngua [l][1] - 1][n] != point_cgua [l] && atom.bonds [point_ngua [l][1] - 1][n] != 0)
			{	
				strcat (rule_3 [l], atom.name [atom.bonds [point_ngua [l][1] - 1][n] - 1]);
				break;
			}
			else continue;
		}
		strcat (rule_3 [l], " 150 0\n");
		a ++; 		
	}

	if (point_ngua [l][0] == 0 || point_cgua [l] == 0 || point_ngua [l][2] == 0 || 
	    atom.bonds [point_ngua [l][2] - 1][0] == 0 ||
    	    atom.bonds [point_ngua [l][2] - 1][1] == 0 ||
	    atom.bonds [point_ngua [l][2] - 1][2] == 0) continue;

	if (b == 0)
	{	
		strcat (rule_4 [l], "mol.");
		strcat (rule_4 [l], atom.name [point_ngua [l][0] - 1]);
		strcat (rule_4 [l], " mol.");
		strcat (rule_4 [l], atom.name [point_cgua [l] - 1]);
		strcat (rule_4 [l], " mol.");
		strcat (rule_4 [l], atom.name [point_ngua [l][2] - 1]);
		strcat (rule_4 [l], " mol.");
		for (n = 0; n < 3; n++)
		{
			if (atom.bonds [point_ngua [l][2] - 1][n] != point_cgua [l] && atom.bonds [point_ngua [l][2] - 1][n] != 0)
			{
				strcat (rule_4 [l], atom.name [atom.bonds [point_ngua [l][2] - 1][n] - 1]);
				break;
			}
			else continue;
		}
		strcat (rule_4 [l], " 150 0\n");
		b ++; 		
	}

	if (point_ngua [l][2] == 0 || point_cgua [l] == 0 || point_ngua [l][0] == 0 || 
	    atom.bonds [point_ngua [l][0] - 1][0] == 0 ||
	    atom.bonds [point_ngua [l][0] - 1][1] == 0 ||
    	    atom.bonds [point_ngua [l][0] - 1][2] == 0) continue;

	if (d == 0)
	{	
		strcat (rule_5 [l], "mol.");
		strcat (rule_5 [l], atom.name [point_ngua [l][2] - 1]);
		strcat (rule_5 [l], " mol.");
		strcat (rule_5 [l], atom.name [point_cgua [l] - 1]);
		strcat (rule_5 [l], " mol.");
		strcat (rule_5 [l], atom.name [point_ngua [l][0] - 1]);
		strcat (rule_5 [l], " mol.");
		for (n = 0; n < 3; n++)
		{
			if (atom.bonds [point_ngua [l][0] - 1][n] != point_cgua [l] && atom.bonds [point_ngua [l][0] - 1][n] != 0)
			{	
				strcat (rule_5 [l], atom.name [atom.bonds [point_ngua [l][0] - 1][n] - 1]);
				break;
			}
			else continue;
		}
		strcat (rule_5 [l], " 150 0\n");
		d ++; 		
	}
}


// the sixth rule 
for (j = 0; j < e; j++)
{
	if (i = point_nplan [j])
	{
		if (atom.bondtypes[point_nplan [j] - 1][0] == 2 || atom.bondtypes[point_nplan [j] - 1][1] == 2) continue;
		if (atom.bondtypes[point_nplan [j] - 1][0] == 0 || atom.bondtypes[point_nplan [j] - 1][1] == 0 ||
		    atom.bondtypes[point_nplan [j] - 1][2] == 0) 
		{
				fprintf (warn, "%s\n", "Warning: N.pl3 atom with 2 single bonds");
				write_warn = 1;
				continue;
		}
		else
		{
			if (point_nplan [j] == 0 || atom.bonds [point_nplan [j] - 1] [0] == 0 
			|| atom.bonds [point_nplan [j] - 1] [1] == 0 || atom.bonds [point_nplan [j] - 1] [2] == 0) continue;
			else
			{
			q ++;
			strcat (rule_6 [q], "mol.");
			strcat (rule_6 [q], atom.name [point_nplan [j] - 1]);
			strcat (rule_6 [q], " mol.");
			strcat (rule_6 [q], atom.name [atom.bonds [point_nplan [j] - 1] [0] - 1]);
			strcat (rule_6 [q], " mol.");
			strcat (rule_6 [q], atom.name [atom.bonds [point_nplan [j] - 1] [1] - 1]);
			strcat (rule_6 [q], " mol.");
			strcat (rule_6 [q], atom.name [atom.bonds [point_nplan [j] - 1] [2] - 1]);
			strcat (rule_6 [q], " 150 0\n");			
			}
		}
	}	
}

//  the seventh rule 
for (j = 0; j < f; j++)
{
	if (i = point_n2 [j])
	{
		if (atom.bondtypes[point_n2 [j] - 1][0] == 2 || atom.bondtypes[point_n2 [j] - 1][1] == 2) continue;
		else
		{
			if (point_n2 [j] == 0 || atom.bonds [point_n2 [j] - 1] [0] == 0 
			|| atom.bonds [point_n2 [j] - 1] [1] == 0 || atom.bonds [point_n2 [j] - 1] [2] == 0) continue;
			else
			{
			p ++;
			strcat (rule_7 [p], "mol.");
			strcat (rule_7 [p], atom.name [point_n2 [j] - 1]);
			strcat (rule_7 [p], " mol.");
			strcat (rule_7 [p], atom.name [atom.bonds [point_n2 [j] - 1] [0] - 1]);
			strcat (rule_7 [p], " mol.");
			strcat (rule_7 [p], atom.name [atom.bonds [point_n2 [j] - 1] [1] - 1]);
			strcat (rule_7 [p], " mol.");
			strcat (rule_7 [p], atom.name [atom.bonds [point_n2 [j] - 1] [2] - 1]);
			strcat (rule_7 [p], " 150 0\n");			
			}
		}
	}	
}

// Writing information about bonds in mol file
for (j = 0; j < bonds_number; j++)		
fprintf (mol, "%s%s %s%s %s\n", "mol.", atom.name [bond.origin [j] - 1], 
	 "mol.", atom.name [bond.target [j] - 1], bond.type [j]);  

// End of mol file - it depends on the availability of amid- or guanidine type bonds, as well as from N.pl3 type
if (count_gua == 0 && r == 0 && s == 0 && q == 0 && p == 0) 
   fprintf (mol, "%s\n%s\n%s\n", "0", "0", "0"); // mol file have to end with three zeros
	else
	{
		fprintf (mol, "%s\n", "0"); 
		fprintf (mol, "%i %s\n", (t + r + s + 3*count_gua + q + p), "hybrid"); 

		for (l = 0; l < count_amid; l++) 
		{
			if (strcmp (rule_0 [l], "") == 0) continue;
			else fprintf (mol, "%s", rule_0 [l]); 
		}

		for (l = 0; l < count_amid; l++) 
		{
			if (strcmp (rule_1 [l], "") == 0) continue;
			else fprintf (mol, "%s", rule_1 [l]); 
		}

		for (l = 0; l < s; l++) 
		{
			if (strcmp (rule_2 [l], "") == 0) continue;
			else fprintf (mol, "%s", rule_2 [l]); 
		}
		for (l = 0; l < count_gua; l++) 
		{
			fprintf (mol, "%s", rule_3 [l]); 
			fprintf (mol, "%s", rule_4 [l]); 
			fprintf (mol, "%s", rule_5 [l]); 
		}
		for (l = 1; l < q + 1; l++) 
		{
			if (strcmp (rule_6 [l], "") == 0) continue;
			else fprintf (mol, "%s", rule_6 [l]); 
		}
		for (l = 1; l < p + 1; l++) 
		{
			if (strcmp (rule_7 [l], "") == 0) continue;
			else fprintf (mol, "%s", rule_7 [l]); 
		}
		fprintf (mol, "%s\n", "0"); 	
	}

// Clean of warning file if there is no warnings
if (write_warn == 0) 
{
	remove ("warning"); 		// Remove file with written molecule name
	warn = fopen ("warning", "w" );	// Create a new empty file
}


// Before termination, free up space and close files
// Free located for atom_name and type1 memory
for (i = 0; i < max_numb_atoms; ++i)
{
	free (atom.name [i]); 
	free (atom.type [i]);
	free (rule_0 [i]);
	free (rule_1 [i]);
	free (rule_2 [i]);
	free (rule_3 [i]);
	free (rule_4 [i]);
	free (rule_5 [i]);
	free (rule_6 [i]);
	free (rule_7 [i]);
}

for (j = 0; j < max_numb_bonds; ++j)
{
	free (bond.type [j]);
}

// Close working files
fclose (mol2);		// Close *.mol2 file 
fclose (mol);		// Close template file   
fclose (pdb);		// Close *.pdb file  
fclose (warn);		// Close warning file  
}

