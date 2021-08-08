import java.io.FileWriter;

public class BinaryTree {
		TreeNode root;

		
		BinaryTree() {
			//can be use to setroot
		}

		public void preOrderTraversal(TreeNode n, FileWriter out) throws Exception {
			if(this.isLeaf(n))
				n.printNode(n, out);
			else {
				n.printNode(n, out);
				preOrderTraversal(n.left, out);
				preOrderTraversal(n.right, out);
			}

		}

		public void inOrderTraversal(TreeNode n, FileWriter out) throws Exception {
			if(this.isLeaf(n))
				n.printNode(n, out);
			else {
				inOrderTraversal(n.left, out);
				n.printNode(n, out);	
				inOrderTraversal(n.right, out);
			}

		}

		public void postOrderTraversal(TreeNode n, FileWriter out) throws Exception {
			if(this.isLeaf(n))
				n.printNode(n, out);
			else {
				postOrderTraversal(n.left, out);
				postOrderTraversal(n.right, out);
				n.printNode(n, out);
			}

		}

		public boolean isLeaf(TreeNode n) {
			return n.left == null && n.right == null;
		}

}
