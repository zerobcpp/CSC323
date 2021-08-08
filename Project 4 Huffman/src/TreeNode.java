import java.io.File;
import java.io.FileWriter;


public class TreeNode {
		String chStr;
		int frequency;
		String code;
		TreeNode left, right, next;

		TreeNode(String chStr, int frequency, String code, TreeNode left, TreeNode right, TreeNode next) {
			this.chStr = chStr;
			this.frequency = frequency;
			this.code = code;
			this.left = left;
			this.right = right;
			this.next = next;
		}

		public void printNode(TreeNode n, FileWriter Debug) throws Exception {
//			System.out.println(Debug.getPath());
//			FileWriter writer = new FileWriter(Debug);
			String format;
			if (n.next != null && n.left != null && n.right != null) {
				format = String.format("(%s,  %s,  %s,  %s,  %s,  %s)", n.chStr, n.frequency, n.code, n.next.chStr,n.left.chStr, n.right.chStr);
			}
			else if (n.next != null && n.left != null) {
				format = String.format("(%s,  %s,  %s,  %s,  %s)", n.chStr, n.frequency, n.code, n.next.chStr,n.right.chStr);
			}
			else if (n.next != null) {
				format = String.format("(%s,  %s,  %s,  %s)", n.chStr, n.frequency, n.code, n.next.chStr);
			}
			else {
				format = String.format("(%s,  %s,  %s)", n.chStr, n.frequency, n.code);
			}
			Debug.append(format);
			Debug.flush();
		}
} // TreeNode