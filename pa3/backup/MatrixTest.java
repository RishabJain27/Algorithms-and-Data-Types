class MatrixTest{
	public static void main(String args[]) {
		Matrix temp,A,B,temp2;
 	
		
	A = new Matrix(10);
        B = new Matrix(10);
        
        A.changeEntry(1, 1, 1);
        A.changeEntry(2, 2, 1);
        A.changeEntry(3, 3, 1);
        A.changeEntry(6,8,0);

        System.out.println("A Matrix :\n" + A);
        System.out.println("get size of Matrix:\n " + A.getSize());
        System.out.println("get NNZ of Matrix: \n" + A.getNNZ());
        
        B.changeEntry(1,1,4);
        B.changeEntry(2,2,8);
        B.changeEntry(3,3,5);
        B.changeEntry(5,5,0);

        if(! A.equals(B)){
                System.out.println("A is not equal to B");
        }

        temp = B.copy();
        B.makeZero();

        System.out.println("Copy of B matrix: \n" + temp);
        System.out.println("B of zero matrix: \n" + B);

        A.scalarMult(2);

        System.out.println("mult matrix A by constant of 2: \n" + A);

        temp2 = A.add(B);

        System.out.println("Matrix A + B: \n"+ temp2);

        temp2 = A.sub(B);

        System.out.println("Matrix A - B: \n"+ temp2);

        temp2 = A.transpose();

        System.out.println("Matrix A transpose: \n"+ temp2);

        //double count = A.dot(A.data[0],B.data[0]);
        temp2 = A.mult(temp);

        //System.out.println("dot test: " + count);
        System.out.println("A*B: \n"+ temp);
        
	}
}