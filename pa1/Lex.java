//-----------------------------------------------------------------------------
// Alyssa Melton 
// amelton@ucsc.edu
// CS101
// 4/10/18
// Lex.java
//-----------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

class Lex{

	public static void main(String[] args) throws IOException{

		//-Put lines into an array-------------------------------------------------

		Scanner in = null;
		PrintWriter out = null;
		String[] lines = null;
		int numLines = 0;


		// check number of command line 
		// arguments is at least 2: file and target.
		if(args.length != 2){
			System.out.println("Usage: input output");
			System.exit(1);
		}


		//open files
		in = new Scanner(new File(args[0]) );
		out = new PrintWriter(new FileWriter(args[1]));


		// count the number of lines in file
		while( in.hasNextLine() ){
			numLines++;
			in.nextLine();
		}
		in.close();



		//put lines into array
		in = new Scanner(new File(args[0]) );
		lines = new String[numLines];

		for(int i = 0; i < numLines; i++){
			lines[i] = in.nextLine();
		}


		//-Insert the elements of the array in sorted order into List-------------------------------------------------

		List L = new List();
		L.append(0);


		// do insertion sort w/ List methods
		for(int i = 1; i < lines.length; i++){				
			L.moveBack();											// begin at end of list
			while( L.index() >= 0 ){								// not off edge of list
				if (lines[i].compareTo(lines[L.get()]) < 0){		// compare
					L.movePrev();									// decrement
				} else { 
					L.insertAfter(i);								// insert after
					break;											// no reason to continue loop
				}
			}	
			if(L.index() == -1){									// if go off end, then belongs at beginning of list
				L.prepend(i);
			} 															
		}		




														
		//-Print elements in order------------------------------------------------------------
		L.moveFront();
		while(L.index()>=0){
			int x = L.get();
			out.println(lines[x]);
			L.moveNext();
		}

		//close files
		in.close();
		out.close();
	}
}