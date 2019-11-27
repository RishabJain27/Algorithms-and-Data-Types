//Rishab Jain, rjain9, 11/4/17, ListTest.java
class ListTest{
	public static void main(String[] args){
		List A = new List();
		List B = new List();

		A.append(5);
		A.append(4);
		A.append(3);
		A.append(2);
		A.append(1);

		System.out.println(A);

		A.moveFront();
		System.out.println(A.index());
		A.delete();
		System.out.println(A);

		B.append(4);
		B.append(3);
		B.append(2);
		B.append(1);
		if(A.equals(B)){
			System.out.println("The list is equal");
		}

		B.deleteBack();
		System.out.println(B);
		B.deleteFront();
		System.out.println(B);
	}
}