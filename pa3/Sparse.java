//------------------------------------------------------------------------------------------------
// Alyssa Melton 
// amelton@ucsc.edu
// CS101
// 5/15/18
// Sparse.java
//------------------------------------------------------------------------------------------------

import java.io.*;
import java.util.Scanner;

class Sparse{

	public static void main(String[] args) throws IOException{

		//-Put lines into an array-------------------------------------------------

		Scanner in = null;
		PrintWriter out = null;

		// check number of command line 
		// arguments is at least 2: file and target.
		if(args.length != 2){
			System.out.println("Usage: input output");
			System.exit(1);
		}


		//open files
		in = new Scanner(new File(args[0]) );
		out = new PrintWriter(new FileWriter(args[1]));

		//get size values
		int sizeMatrix = in.nextInt();
		int nnzA = in.nextInt();
		int nnzB = in.nextInt();
		
		//construct Matrix A -----------------------------------------------------------------------------------------
		
		Matrix A = new Matrix(sizeMatrix);
		for(int i = 0; i < nnzA; i++) {
			A.changeEntry(in.nextInt(), in.nextInt(), in.nextDouble());
		}
		
		//construct Matrix B -------------------------------------------------------------------------------------------

		Matrix B = new Matrix(sizeMatrix);
		for(int i = 0; i < nnzB; i++) {
			B.changeEntry(in.nextInt(), in.nextInt(), in.nextDouble());
		}
		
		
		//-Print matrix operations-----------------------------------------------------------------------------------
		
		//A has 9 non-zero entries:
		out.println("A has " + A.getNNZ() + " non-zero entries:");
		out.println(A);

		//B has 5 non-zero entries
		out.println("B has " + B.getNNZ() + " non-zero entries:");
		out.println(B);


		//(1.5)*A =
		out.println("(1.5)*A =");
		out.println(A.scalarMult(1.5));
				
		//A+B =
		out.println("A+B =");
		out.println(A.add(B));

		//A+A =
		out.println("A+A = ");
		out.println(A.add(A));
		
		//B-A =
		out.println("B-A = ");
		out.println(B.sub(A));

		//A-A =
		out.println("A-A = ");
		out.println(A.sub(A));

		//Transpose(A) =
		out.println("Transpose(A) =");
		out.println(A.transpose());


		//A*B =
		out.println("A*B =");
		out.println(A.mult(B));

		//B*B =
		out.println("B*B =");
		out.println(B.mult(B));

		//close files
		in.close();
		out.close();
	}
}