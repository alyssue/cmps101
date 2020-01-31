//------------------------------------------------------------------------------------------------
// Alyssa Melton 
// amelton@ucsc.edu
// CS101
// 5/1/18
// Matrix.java
//------------------------------------------------------------------------------------------------


public class Matrix{

	//-Fields for the Matrix class----------------------------------------------------------------
	private List[] row;
	private int size;   // number of rows / collumns
	private int nnz; // number of non-zero elements


	// Constructor
	// Makes a new n x n zero Matrix. pre: n>=1
	public Matrix(int n) {
		row = new List[n+1]; //n+1 indexes because we'll disregard index zero for convenience. 
		for(int i = 1; i < n+1; i++){
			row[i] = new List();
		}
		size = n;
		nnz = 0;
	}

	//-Private inner entry class for entries of matrix that are nonzero---------------------------

   	private class Entry {
		int column;
		double value;

		Entry(int c, double v){
			value = v;
			column = c;
		}

		// overrides Object's equals() method
		public boolean equals(Entry B){
			if(column != B.column) return false;
			if(value != B.value) return false; 
			return true;
		}

		// overrides Object's toString() method
		public String toString(){
			return "(" + column + ", " + value + ")";
		}
	}

	//-Private Helper Functions------------------------------------------------------------------
   	
   	
   	//converts Object into Entry
   	private Entry getEntry(List L) {
   		Entry E = (Entry)L.get();
   		return E;
   	}


	// computes the vector dot product of two matrix rows represented by Lists P and Q. 
	private double dot(List P, List Q){
		double dotProduct = 0;

		P.moveFront();
		Q.moveFront();
		while(P.index() >= 0 && Q.index() >= 0){	//while both cursors are defined
			if (getEntry(P).column == getEntry(Q).column){
				double product = getEntry(P).value * getEntry(Q).value;
				int thisColumn = getEntry(Q).column;
				dotProduct += product;
				P.moveNext();
				Q.moveNext();
			} else if (getEntry(P).column < getEntry(Q).column){
				P.moveNext();
			} else if (getEntry(Q).column < getEntry(P).column){
				Q.moveNext();
			}
		}
		return dotProduct;
	}


	//-Public Access Functions-------------------------------------------------------------------

	// Returns n, the number of rows and columns of this Matrix
	int getSize(){
		return size;
	}

	// Returns the number of non-zero entries in this Matrix
	int getNNZ(){
		return nnz;
	}


	// Overrides Object's toString() Method
	public String toString(){
		String matrixString = "";
		
		for(int i =1; i < getSize()+1; i++){
			if(row[i].length() > 0){
				matrixString += (i + ":");
				row[i].moveFront();
				while(row[i].index() >= 0){
					matrixString += (" " + getEntry(row[i]));
					row[i].moveNext();
				}
				matrixString += "\n";
			}
		}
		return matrixString;
	}


	public boolean equals(Object X){
		if (this == X){
			return true;
		}

		if( X instanceof Matrix){
			Matrix M = (Matrix) X;
			if(getSize() == 0 && M.getSize() == 0) return true;
			if (getSize() != M.getSize()) return false;  	//if the sizes aren't the same, they're obviously not equal
			if(getNNZ() != M.getNNZ()) return false; 		//if number of NNZs aren't the same, they're obviously not equal
			if(!row.equals(M.row)) return false; 			//if arrays aren't the same, not equal.
			return true;
		}

		return false;
	
	}


	//-Public Manipulation Functions--------------------------------------------------------------


	// sets this Matrix to the zero state
	void makeZero(){
		for(int i = 1; i < row.length; i++){
			row[i].clear();
		}
		nnz = 0;

	}


	// returns a new Matrix having the same entries as this Matrix
	Matrix copy(){
		Matrix copy = new Matrix(size);
		for(int i = 1; i < size+1; i++){	//for each row
			row[i].moveFront();
			while(row[i].index() >= 0){			//and for each NNZ column
				int c = getEntry(row[i]).column;
				double v = getEntry(row[i]).value;
				copy.changeEntry(i, c, v);
				row[i].moveNext();
			}
		}
		return copy;
	}


	// changes ith row, jth column of this Matrix to x
	// pre: 1<=i<=getSize(), 1<=j<=getSize()
	void changeEntry(int i, int j, double value) throws RuntimeException{
		if(!(1 <= i && i <= getSize()) || !(1 <= j && j <= getSize())) throw new RuntimeException("Cannot operate on nonexistent index.");

		if(row[i].length() == 0){					// if empty list
			if(value != 0){							// and value is non zero
				Entry E = new Entry(j, value);
				row[i].prepend(E);	
				nnz++;								// insert
			}
		} else { 									// if nonempty list
			row[i].moveFront();
			while( row[i].index() >= 0 && getEntry(row[i]).column < j){  //move cursor to column j, 1st column larger than j, or fall off.
				row[i].moveNext();
			}
			if(row[i].index() == -1) { 				//fell off end of list, A[i][j] is zero entry and all entrees columns are < j
				if(value != 0){						//insert NNZ 
					Entry E = new Entry(j, value);
					row[i].append(E);
					nnz++;
				} 
			} else if (getEntry(row[i]).column == j) { 	// if A[i, j] is NNZ
				if(value == 0){						// if value == 0
					row[i].delete();					// delete
					nnz--;
				} else {							// if value != 0;
					getEntry(row[i]).value = value;		// overwrite
				}
			} else {								// if A[i, j] is not NNZ
				Entry E = new Entry(j, value);
				row[i].insertBefore(E);				// insert before 1st column larger than j
				nnz++;
			}
		}
	}



	// returns a new Matrix that is the scalar product of this Matrix with x
	Matrix scalarMult(double x){
		Matrix mult = new Matrix(size+1);
		for(int i = 1; i < size+1; i++){	//for each row
			row[i].moveFront();
			while(row[i].index() >= 0){			//and for each NNZ column
				int c = getEntry(row[i]).column;
				double v = x * getEntry(row[i]).value;
				mult.changeEntry(i, c, v);
				row[i].moveNext();
			}
		}
		return mult;
	}

	
	// returns a new Matrix that is the sum of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix add(Matrix M) throws RuntimeException{
		if(getSize() != M.getSize()) throw new RuntimeException("Cannot add matrices of different size.");
		Matrix sum = M.copy();

		for(int i=1; i < getSize()+1; i++){
			row[i].moveFront();
			while(row[i].index() >= 0){								//go through all NNZs of row[i]
				int column = getEntry(row[i]).column;				//get column
				double value = getEntry(row[i]).value;				//get value

				M.row[i].moveFront();								//go through M.row[i] to see where Entry belongs.
				while(M.row[i].index() >= 0 && getEntry(M.row[i]).column < column){
					M.row[i].moveNext();
				}
				if(M.row[i].index() == -1){
					Entry E = new Entry(column, value);
					sum.row[i].append(E);
					nnz++;
				} else if(getEntry(M.row[i]).column == column){
					getEntry(M.row[i]).value += value;
				}else if(getEntry(M.row[i]).column < column){ //if stopped before column
					sum.changeEntry(i, column, value);
				} 
				row[i].moveNext();
			}
		}
		return sum;
	}
	


	/*
	// returns a new Matrix that is the sum of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix add(Matrix M) throws RuntimeException{
		if(getSize() != M.getSize()) throw new RuntimeException("Cannot add matrices of different size.");
		Matrix sum = new Matrix(size+1);

		for(int i=1; i < size+1; i++){
			row[i].moveFront();
			M.row[i].moveFront();

			while(row[i].index() >= 0 && M.row[i].index() >= 0){	//while both cursors are defined
				if (getEntry(row[i]).column == getEntry(M.row[i]).column){
					double sumValue = getEntry(row[i]).value + getEntry(M.row[i]).value;
					int thisColumn = getEntry(M.row[i]).column;
					sum.changeEntry(i, thisColumn, sumValue);
					row[i].moveNext();
					M.row[i].moveNext();
				} else if (getEntry(row[i]).column < getEntry(M.row[i]).column){
					double thisValue = getEntry(row[i]).value;
					int thisColumn = getEntry(row[i]).column;
					sum.changeEntry(i, thisColumn, thisValue);
					row[i].moveNext();
				} else if (getEntry(M.row[i]).column < getEntry(row[i]).column){
					double thisValue = getEntry(M.row[i]).value;
					int thisColumn = getEntry(M.row[i]).column;
					sum.changeEntry(i, thisColumn, thisValue);
					M.row[i].moveNext();
				}
			}

			if( row[i].index() >= 0 && M.row[i].index() < 0 ){ // if M falls off or is empty
				while( row[i].index() >= 0){
					int c = getEntry(row[i]).column;
					double v = getEntry(row[i]).value;
					sum.changeEntry(i, c, v);
					row[i].moveNext();
				}
			} else if ( row[i].index() < 0 && M.row[i].index() >= 0){ //if A falls off or is empty
				while( M.row[i].index() >= 0){
					int c = getEntry(M.row[i]).column;
					double v = getEntry(M.row[i]).value;
					sum.changeEntry(i, c, v);
					M.row[i].moveNext();
				}
			}
		}
		return sum;
	}
	


	// returns a new Matrix that is the sum of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix add(Matrix M) throws RuntimeException{
		Matrix sum = new Matrix(getSize());

		for(int i = 1; i < getSize()+1; i++){
			row[i].moveFront();
			M.row[i].moveFront();

			while(row[i].index() >= 0 && M.row[i].index() >= 0){
				if(getEntry(row[i]).column == getEntry(M.row[i]).column){
					int c = getEntry(row[i]).column;
					double v = getEntry(row[i]).value + getEntry(M.row[i]).value;
					sum.changeEntry(i, c, v);
					row[i].moveNext();
					M.row[i].moveNext();
				} else if(getEntry(row[i]).column < getEntry(M.row[i]).column){
					int c = getEntry(row[i]).column;
					double v = getEntry(row[i]).value;
					sum.changeEntry(i, c, v);
					row[i].moveNext();
				} else if (getEntry(row[i]).column > getEntry(M.row[i]).column){
					int c = M.getEntry(row[i]).column;
					double v = M.getEntry(row[i]).value;
					sum.changeEntry(i, c, v);
					M.row[i].moveNext();
				}
			}

			while(row[i].index() >= 0){	//M falls off
				int c = getEntry(row[i]).column;
				double v = getEntry(row[i]).value;
				sum.changeEntry(i, c, v);
				row[i].moveNext();
			}

			while(M.row[i].index() >= 0){ //A falls off
				int c = getEntry(M.row[i]).column;
				double v = getEntry(M.row[i]).value;
				sum.changeEntry(i, c, v);
				M.row[i].moveNext();
			}
		}

		return sum;
	}
	*/



	// returns a new Matrix that is the difference of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix sub(Matrix M) throws RuntimeException{
		if(getSize() != M.getSize()) throw new RuntimeException("Cannot subtract matrices of different size.");
		Matrix sub = new Matrix(size+1);

		for(int i=1; i < size+1; i++){
			row[i].moveFront();
			M.row[i].moveFront();

			while(row[i].index() >= 0 && M.row[i].index() >= 0){	//while both cursors are defined
				if (getEntry(row[i]).column == getEntry(M.row[i]).column){
					double subValue = getEntry(row[i]).value - getEntry(M.row[i]).value;
					int thisColumn = getEntry(M.row[i]).column;
					sub.changeEntry(i, thisColumn, subValue);
					row[i].moveNext();
					M.row[i].moveNext();
				} else if (getEntry(row[i]).column < getEntry(M.row[i]).column){
					double thisValue = getEntry(row[i]).value;
					int thisColumn = getEntry(row[i]).column;
					sub.changeEntry(i, thisColumn, thisValue);
					row[i].moveNext();
				} else if (getEntry(M.row[i]).column < getEntry(row[i]).column){
					double thisValue = getEntry(M.row[i]).value;
					thisValue = -thisValue;
					int thisColumn = getEntry(M.row[i]).column;
					sub.changeEntry(i, thisColumn, thisValue);
					M.row[i].moveNext();
				}
			}

			if( row[i].index() >= 0 && M.row[i].index() < 0 ){ // if M falls off or is empty
				while( row[i].index() >= 0){
					int c = getEntry(row[i]).column;
					double v = getEntry(row[i]).value;
					sub.changeEntry(i, c, v);
					row[i].moveNext();
				}
			} else if ( row[i].index() < 0 && M.row[i].index() >= 0){ //if A falls off or is empty
				while( M.row[i].index() >= 0){
					int c = getEntry(M.row[i]).column;
					double v = getEntry(M.row[i]).value;
					v = -v;
					sub.changeEntry(i, c, v);
					M.row[i].moveNext();
				}
			}
		}
		return sub;
	}


	// returns a new Matrix that is the transpose of this Matrix
	Matrix transpose(){
		Matrix B = new Matrix(getSize());
		for(int i = 1; i < size+1; i++){
			if(row[i].length() != 0){
				row[i].moveFront();
				while(row[i].index() >= 0){
					B.changeEntry(getEntry(row[i]).column, i, getEntry(row[i]).value);
					row[i].moveNext();
				}
			}
		}
		return B;
	}


	// returns a new Matrix that is the product of this Matrix with M
	// pre: getSize()==M.getSize()
	Matrix mult(Matrix M) throws RuntimeException{
		if(M.getSize() != getSize()) throw new RuntimeException("cannot multiply matrices of different length.");

		Matrix B = M.transpose();
		Matrix crossProduct = new Matrix(getSize());
		for(int i = 1; i < getSize()+1; i++){
			for(int j = 1; j < getSize()+1; j++){
				crossProduct.changeEntry(i, j, dot(row[i], B.row[j]));
			}
		}
		return crossProduct;
	} 

}