import java.io.*;

public class linkedList {
		TreeNode listHead;

		linkedList() {
			TreeNode dummy = new TreeNode("Dummy", 0, "", null, null, null);
			listHead = dummy;
		}

		public void insertNewNode(TreeNode n) {
			TreeNode current = listHead;
			while (current.next != null && current.next.frequency < n.frequency)
				current = current.next;
			if (current.frequency == n.frequency) {
				n.next = current.next;
				current.next = n;
			} else {
				n.next = current.next;
				current.next = n;
			}
		}

		public void PrintList(TreeNode n, FileWriter DebugWriter) throws Exception {
			TreeNode current = listHead;
			while(current != null) {
				current.printNode(current, DebugWriter);
				current = current.next;
			}
			DebugWriter.write("---End\n");
			DebugWriter.flush();
		}
}