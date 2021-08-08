import java.io.*;
import java.util.Scanner;

public class HuffmanCoding {
	int[] charCountArr = new int[256];
	String[] charCode = new String[256];
	linkedList HuffmanLinkedList = new linkedList();
	BinaryTree HuffmanBinaryTree = new BinaryTree();

	public void computeCharCounts(File in, int[] Chararray) throws Exception {
		Scanner reader = new Scanner(in);
		String c;
		while (reader.hasNext()) {
			c = reader.nextLine()+"\n";
			for (char i : c.toCharArray()) {
				int index = i - '0' + 48;
				Chararray[index]++;
				if(i == '\n')
				Chararray[10]++;
				
			}
			//System.out.print(c);
		}
	}

	public void printCountArr(FileWriter Writer) throws Exception {
		for (int i = 0; i < charCountArr.length; i++) {
			if (charCountArr[i] != 0)
				Writer.write("Char" + i + '\t' + charCountArr[i] + "\n");
		}
		Writer.flush();
	}

	public void constructHuffmanLList(int[] arr, FileWriter DebugFile) throws Exception {
		int index = 0;
		linkedList test = new linkedList();
		while (index < 256) {
			if (charCountArr[index] > 0) {
				char c = (char) (index + '0' - 48);
				String s = "";
				s += c;
				if (index == 32)
					s = " ";
				if (index == 10)
					s = "\n";
				int prob = charCountArr[index];
				TreeNode n = new TreeNode(s, prob, "", null, null, null);
				test.insertNewNode(n);
				test.PrintList(test.listHead, DebugFile);
			}
			index++;
		}
		// this.listHead = test.listHead;
		HuffmanLinkedList = test;
		//System.out.println("LList Finish, passing the HuffmanList to the next function");
	}

	public void constructHuffmanBinTree(TreeNode n, FileWriter out) throws Exception {
		while (n.next.next != null) {
			String chstr = n.next.chStr + n.next.next.chStr;
			int prob = n.next.frequency + n.next.next.frequency;
			TreeNode newNode = new TreeNode(chstr, prob, "", n.next, n.next.next, null);
			n.next = n.next.next.next;
			HuffmanLinkedList.insertNewNode(newNode);
			HuffmanLinkedList.PrintList(HuffmanLinkedList.listHead, out);
		}
		BinaryTree Huffbintree = new BinaryTree();
		Huffbintree.root = HuffmanLinkedList.listHead.next;
		HuffmanBinaryTree = Huffbintree;
	}

	public void constructCharCode(TreeNode n, String code) {
		int index = 0;
		if (HuffmanBinaryTree.isLeaf(n)) {
			n.code = code;
			index = n.chStr.charAt(0) - '0' + 48;
			charCode[index] = code;
		} else {
			constructCharCode(n.right, code + '1');
			constructCharCode(n.left, code + '0');
		}

	}

	public void Encode(File orgFile, FileWriter compFile) throws Exception {
		Scanner reader = new Scanner(orgFile);
		int index;
		String code;
		File compnoindex = new File(orgFile.toString().replaceAll(".txt", "") + "_index.txt");
		compnoindex.createNewFile();
		FileWriter noindex = new FileWriter(compnoindex);
		while (reader.hasNext()) {
			String s = reader.nextLine()+"\n";
			for (char i : s.toCharArray()) {
				index = (char) (i - '0' + 48);
				code = charCode[index];
				compFile.append(String.valueOf(index) + ":");
				compFile.append(code + "    ");
				compFile.flush();
				noindex.append(code + '\n');
				noindex.flush();
			}
		}

	}

	public void Decode(File compFile, FileWriter DecompFile) throws Exception {
		TreeNode spot = HuffmanBinaryTree.root;
		Scanner reader = new Scanner(compFile);
		String s;
		/*
		 * while(reader.hasNext()) { s = reader.nextLine(); for (char c :
		 * s.toCharArray()) { if (c=='1') spot = spot.right; else if (c == '0') spot =
		 * spot.left; else throw new
		 * Exception("Error! The compress file contains invalid character\n"); } if
		 * (HuffmanBinaryTree.isLeaf(spot)) { DecompFile.append(spot.chStr);
		 * DecompFile.flush(); spot = HuffmanBinaryTree.root; } }
		 * if(!HuffmanBinaryTree.isLeaf(spot)) throw new
		 * Exception("Error: The compress file is corrupted!\n");
		 */
		while (reader.hasNext()) {
			if (HuffmanBinaryTree.isLeaf(spot)) {
				DecompFile.append(spot.chStr);
				DecompFile.flush();
				spot = HuffmanBinaryTree.root;
			}
			s = reader.nextLine();
			for (char c : s.toCharArray()) {
				if (c == '0')
					spot = spot.left;
				else if (c == '1')
					spot = spot.right;
				else
					throw new Exception("Error the compress file contains invalid character\n");
			}
			if (!HuffmanBinaryTree.isLeaf(spot))
				throw new Exception("Error: The compress file is corrupted\n");
		}
	}

	public void UI() throws Exception {
		String nameOrg;
		String nameCompress;
		String nameDecompress;
		char flag = ' ';
		Scanner reader = new Scanner(System.in);
		while (true) {
			System.out.println("Enter any character to proceed, but N to stop");
			flag = reader.nextLine().charAt(0);
			if (flag == 'N') {
				System.out.println("The loop is breaking\n");
				break;
			}
			System.out.println("Enter the file you wish to read:");
			nameOrg = reader.nextLine();
			nameCompress = nameOrg + "_Compressed.txt";
			nameDecompress = nameOrg + "_Decompressed.txt";
			nameOrg += ".txt";
			File compress = new File(nameCompress);
			FileWriter compressWriter = new FileWriter(compress);
			File decompress = new File(nameDecompress);
			FileWriter decompressWriter = new FileWriter(nameDecompress);
			File Original = new File(nameOrg);
			compress.createNewFile();
			decompress.createNewFile();
			File temp = new File(nameOrg.replaceAll(".txt", "") + "_index.txt");
			Encode(Original, compressWriter);
			Decode(temp, decompressWriter);
			
			compressWriter.close();
			decompressWriter.close();
		}

	}
}