//Rishab Jain,rjain9, pa3, cmps101,11/4/17, Matrix.java
class Matrix{
	private class Entry{
    	// Fields
		private int column;
    	private double value;
      
    	// Constructor
    	Entry(double value, int column) { 
        	this.value = value; 
        	this.column = column;
        }

    	// toString()
    	// Overrides Object's toString() method.
    	public String toString() { 
        	return "("+String.valueOf(column) + ", "+String.valueOf(value)+")";
        }
        
        // equals(): overrides Object's equals() method
      	public boolean equals(Object x){
        	boolean eq = false;
        	Entry that;
        	if(x instanceof Entry){
            	that = (Entry) x;
            	eq = (this.value==that.value && this.column==that.column);
        	}
         	return eq;
      	}
    }

    public int sizeOfMatrix;
    List data[];
    
    // Constructor
    // Makes a new n x n zero Matrix. pre: n>=1
	Matrix(int n){
		if(n<1){
			throw new RuntimeException(
            "Matrix Error: Matrix() called on empty Matrix");
		}
		else{
			sizeOfMatrix = n;
			data = new List[sizeOfMatrix];
			for(int i = 0; i < sizeOfMatrix; i++){
				data[i] = new List();
			}
		}
	}

	// Access functions
	
	// Returns n, the number of rows and columns of this Matrix
	int getSize(){
		return sizeOfMatrix;
	}

	// Returns the number of non-zero entries in this Matrix
	int getNNZ(){
		int zeroCounter = 0;
		for(int i=0; i<sizeOfMatrix; i++){
			zeroCounter = zeroCounter + data[i].length();
		}
		return zeroCounter;
		
	}

	// overrides Object's equals() method
	public boolean equals(Object x){
		Matrix temp;
		
		if(x instanceof Matrix){
			temp = (Matrix)x;
			if(sizeOfMatrix != temp.getSize()){
				return false;
			}
			
			for(int i=0; i<sizeOfMatrix;i++){
				data[i].moveFront();
				temp.data[i].moveFront();
				
				if(temp.data[i].length() != data[i].length()){
					return false;
				}
				
				while(data[i].index() >= 0 && temp.data[i].index()>=0 ){
					if( !(data[i].get().equals(temp.data[i].get())) ){
						return false;
					}

					data[i].moveNext();
					temp.data[i].moveNext();
				}
			}
			return true;
		}
		else{
			return false;
		}

	}

	// Manipulation procedures

	// sets this Matrix to the zero state
	void makeZero(){
		for(int i=0;i<sizeOfMatrix;i++){
			data[i].clear();
		}
	}

	// returns a new Matrix having the same entries as this Matrix
	Matrix copy(){
		Matrix temp = new Matrix(sizeOfMatrix);
		for(int i=0;i<sizeOfMatrix;i++){
			data[i].moveFront();
			
			while(data[i].index()>=0){
				Entry tempE = new Entry(((Entry)data[i].get()).value , ((Entry)data[i].get()).column );
				temp.data[i].append(tempE);
				data[i].moveNext();
			}

		}
		return temp;
	}

	// changes ith row, jth column of this Matrix to x
	// pre: 1<=i<=getSize(), 1<=j<=getSize()
	void changeEntry(int i, int j, double x){
		if (i<1 || i>getSize()) {
			throw new RuntimeException(
            "Matrix Error: changeEntry() called on invalid entry");
		}
		if (j<1 || j>getSize()) {
			throw new RuntimeException(
            "Matrix Error: changeEntry() called on invalid entry");
		}
		
		data[i-1].moveFront();

		if(data[i-1].length() == 0){
			if(x != 0){
				Entry tempE = new Entry(x,j);
				data[i-1].append(tempE);
			}
		}
		else if( j < ((Entry)data[i-1].get()).column){
			if( x != 0){
				Entry tempE = new Entry(x,j);
				data[i-1].prepend(tempE);
			}
		}
		else if(j == ((Entry)data[i-1].get()).column){
			((Entry)data[i-1].get()).value = x;
			if(x == 0){
				data[i-1].delete();
			}
		}
		else{
			data[i-1].moveBack();
			if(j>((Entry)data[i-1].get()).column){
				if(x != 0){
					Entry tempE = new Entry(x,j);
					data[i-1].append(tempE);
				}
			}
			else if(j == ((Entry)data[i-1].get()).column){
				((Entry)data[i-1].get()).value = x;
				if(x == 0){
					data[i-1].delete();
				}

			}
			else{
				data[i-1].moveFront();
				while(j>((Entry)data[i-1].get()).column){
					data[i-1].moveNext();
				}

				if(j==((Entry)data[i-1].get()).column){
					((Entry)data[i-1].get()).value = x;
					if(x == 0){
						data[i-1].delete();
					}
				}
				else{
					Entry tempE = new Entry(x,j);
					data[i-1].insertBefore(tempE);
					if(x==0){
						data[i-1].movePrev();
						data[i-1].delete();
					}
				}
			}
		}
	}

	// returns a new Matrix that is the scalar product of this Matrix with x
	Matrix scalarMult(double x){
		Matrix temp = new Matrix(sizeOfMatrix);

		for(int i =0;i<sizeOfMatrix;i++){
			data[i].moveFront();

			while(data[i].index()>=0){
				Entry tempE = new Entry(((Entry)data[i].get()).value , ((Entry)data[i].get()).column );
				temp.data[i].append(tempE);
				if(temp.data[i].length() == 1){
					temp.data[i].moveFront();
				}
				else{
					temp.data[i].moveNext();
				}
				((Entry)temp.data[i].get()).value = ((Entry)data[i].get()).value * x;
				data[i].moveNext();
			}
		}
		return temp;	
	}

	// returns a new Matrix that is the sum of this Matrix with M
 	// pre: getSize()==M.getSize()
	Matrix add(Matrix M){
		if( getSize() != M.getSize()){
			throw new RuntimeException(
            "Matrix Error: add() called on matrix that are not equal");
		}
		Matrix temp = new Matrix(sizeOfMatrix);
		


		if(equals(M)){
			for(int i =0;i<sizeOfMatrix;i++){
				int columnCounter = 0;
				data[i].moveFront();
				M.data[i].moveFront();


				while(data[i].index()>=0 || M.data[i].index()>=0){
					columnCounter++;
					
					if( (data[i].index()>=0) && (M.data[i].index() >= 0) && (((Entry)data[i].get()).column == columnCounter) && (((Entry)M.data[i].get()).column==columnCounter) ){
						Entry tempE = new Entry(((Entry)data[i].get()).value + ((Entry)M.data[i].get()).value,((Entry)data[i].get()).column);
						if( (  (((Entry)data[i].get()).value + ((Entry)M.data[i].get()).value ) != 0  )  ){
							temp.data[i].append(tempE);
							data[i].moveNext();
						}
						else{
							data[i].moveNext();
						}
					}

				}

			}
			return temp;
	    }


		for(int i =0;i<sizeOfMatrix;i++){
			
			int columnCounter = 0;
			data[i].moveFront();
			M.data[i].moveFront();

			while(data[i].index()>=0 || M.data[i].index()>=0){
				columnCounter++;
				if( (data[i].index()>=0) && (M.data[i].index() >= 0) && (((Entry)data[i].get()).column == columnCounter) && (((Entry)M.data[i].get()).column==columnCounter) ){
					Entry tempE = new Entry(((Entry)data[i].get()).value + ((Entry)M.data[i].get()).value,((Entry)data[i].get()).column);
					if( (  (((Entry)data[i].get()).value + ((Entry)M.data[i].get()).value ) != 0  )  ){
						temp.data[i].append(tempE);
						data[i].moveNext();
						M.data[i].moveNext();
					}
					else{
						data[i].moveNext();
						M.data[i].moveNext();
				    }
				}
				else if( data[i].index() >= 0 && ((Entry)data[i].get()).column == columnCounter){
					Entry tempE = new Entry(((Entry)data[i].get()).value , ((Entry)data[i].get()).column );
					temp.data[i].append(tempE);
					data[i].moveNext();
				}
				else if( M.data[i].index() >= 0 && ((Entry)M.data[i].get()).column == columnCounter){
					Entry tempE = new Entry(((Entry)M.data[i].get()).value , ((Entry)M.data[i].get()).column );
					temp.data[i].append(tempE);
					M.data[i].moveNext();
					
				}

			}

		}
		return temp;
		
	}
	// returns a new Matrix that is the difference of this Matrix with M
 	// pre: getSize()==M.getSize()
	Matrix sub(Matrix M){
		if( getSize() != M.getSize()){
			throw new RuntimeException(
            "Matrix Error: add() called on matrix that are not equal");
		}
		Matrix temp = new Matrix(sizeOfMatrix);


		if(equals(M)){
			return temp;
	    }
		

		for(int i =0;i<sizeOfMatrix;i++){
			
			int columnCounter = 0;
			data[i].moveFront();
			M.data[i].moveFront();

			while(data[i].index()>=0 || M.data[i].index()>=0){
				columnCounter++;
				if( (data[i].index()>=0) && (M.data[i].index() >= 0) && (((Entry)data[i].get()).column == columnCounter) && (((Entry)M.data[i].get()).column==columnCounter) ){
					Entry tempE = new Entry(((Entry)data[i].get()).value - ((Entry)M.data[i].get()).value,((Entry)data[i].get()).column);
					if( ( ((Entry)data[i].get()).value - ((Entry)M.data[i].get()).value ) != 0){
						temp.data[i].append(tempE);
						data[i].moveNext();
						M.data[i].moveNext();

					}
					else{
						data[i].moveNext();
						M.data[i].moveNext();
				    }
				}
				else if( data[i].index() >= 0 && ((Entry)data[i].get()).column == columnCounter){
					Entry tempE = new Entry(((Entry)data[i].get()).value , ((Entry)data[i].get()).column );
					temp.data[i].append(tempE);
					data[i].moveNext();
				}
				else if( M.data[i].index() >= 0 && ((Entry)M.data[i].get()).column == columnCounter){
					Entry tempE = new Entry(0-((Entry)M.data[i].get()).value , ((Entry)M.data[i].get()).column );
					temp.data[i].append(tempE);
					M.data[i].moveNext();
					
				}

			}

		}
		return temp;

	}
	Matrix transpose(){
		Matrix  temp = new Matrix(sizeOfMatrix);
		for(int i=0; i<sizeOfMatrix; i++){
			data[i].moveFront();
			while(data[i].index() >= 0){
				temp.changeEntry(((Entry)data[i].get()).column,i+1,((Entry)data[i].get()).value);
				data[i].moveNext();
			}
		}		
		return temp;
	}

	//Private helper method for mult
	private static double dot(List P, List Q){
		P.moveFront();
		Q.moveFront();
		double count =0;
	
		while(P.index() >= 0 && Q.index() >= 0){
			if( (P.index()>=0) && (Q.index() >= 0) && ((Entry)Q.get()).column == ((Entry)P.get()).column ){
		
				count = count + (((Entry)Q.get()).value * ((Entry)P.get()).value);
				P.moveNext();
				Q.moveNext();
			}
			else if( P.index() >= 0 && ((Entry)P.get()).column < ((Entry)Q.get()).column ){
				P.moveNext();
			}
			else if(Q.index() >= 0 && ((Entry)Q.get()).column < ((Entry)P.get()).column){
				Q.moveNext();
			}
		}
		return count;
	}

	// returns a new Matrix that is the product of this Matrix with M
 	// pre: getSize()==M.getSize()
	Matrix mult(Matrix M){
		if( getSize() != M.getSize()){
			throw new RuntimeException(
            "Matrix Error: add() called on matrix that are not equal");
		}
		Matrix tempM = new Matrix(sizeOfMatrix);
		Matrix temp = M.transpose();

		double value = 0;
		for (int i=1;i<=sizeOfMatrix ;i++){
			for(int k=1;k<=sizeOfMatrix;k++) {
				value = dot(data[i-1],temp.data[k-1]);
				tempM.changeEntry(i,k,value);
			}
		}
		return tempM;
	}

	public String toString(){
		StringBuffer sb = new StringBuffer();
		int rowNumber;
		if(getNNZ() == 0){
			return "";
		}
		else{
			for(int i=0;i<sizeOfMatrix;i++){
				if(data[i].length() > 0){
					rowNumber = i+1;
					sb.append(rowNumber+": ");
				}
				
				data[i].moveFront();

				while(data[i].index() >= 0){
					sb.append(data[i].get());

					data[i].moveNext();
					if(data[i].index() >= 0){
						sb.append(" ");
					}
					else{
						sb.append("\n");
					}
				}
			}
		}

		return new String(sb);
	}

}