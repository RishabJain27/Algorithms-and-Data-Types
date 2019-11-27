//Rishab Jain,rjain9, pa3, cmps101,10/7/17,Sparse.java
import java.util.Scanner;
import java.io.*;

class Sparse{
	public static void main(String[] args) throws IOException{

		Scanner input = null;
		PrintWriter output = null;

		if(args.length != 2){
			System.err.println("Usage: Sparse infile outfile");
			System.exit(1);
		}

		input = new Scanner(new File(args[0]));
		output = new PrintWriter(new FileWriter(args[1]));

		int sizeOfMatrix = input.nextInt();
		int sizeOfA = input.nextInt();
		int sizeOfB = input.nextInt();
		Matrix temp = new Matrix(sizeOfMatrix);
		Matrix temp2 = new Matrix(sizeOfMatrix);

		for(int i=1;i<=sizeOfA;i++){
			int row = input.nextInt();
			int col = input.nextInt();
			double value = input.nextDouble();

			temp.changeEntry(row,col,value);
		}

		for(int k=1;k<=sizeOfB;k++){
			int rowB = input.nextInt();
			int colB= input.nextInt();
			double valueB = input.nextDouble();

			temp2.changeEntry(rowB,colB,valueB);
		}

		output.println("A has "+ sizeOfA + " non-zero entries:");
		output.println(temp);

		output.println("B has "+ sizeOfB + " non-zero entries:");
		output.println(temp2);

		output.println("(1.5)*A =");
		output.println(temp.scalarMult(1.5));

		output.println("A+B =");
		output.println(temp.add(temp2));

		output.println("A+A =");
		output.println(temp.add(temp));

		output.println("B-A =");
		output.println(temp2.sub(temp));

		output.println("A-A =");
		output.println(temp.sub(temp));

		output.println("Transpose(A) =");
		output.println(temp.transpose());

		output.println("A*B =");
		output.println(temp.mult(temp2));

		output.println("B*B =");
		output.println(temp2.mult(temp2));

		input.close();
		output.close();

	}
}