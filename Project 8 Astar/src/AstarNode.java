import java.util.Arrays;

public class AstarNode implements Cloneable{
	int[] configuration;
	int gStar;
	int hStar;
	int fStar; //g*+s*
	AstarNode parent;
	AstarNode next;
	
	AstarNode(){
		gStar = 0;
		parent = null;
		next = null;
	}
	AstarNode(int g, int h, int f){
		gStar = g;
		hStar = h;
		fStar = f;
	}
	public void printNode() {
		
	}
	public void setConf(int []arr) {
		configuration = arr;
	}
	
	@Override
	protected AstarNode clone() throws CloneNotSupportedException {
		return (AstarNode) super.clone();
		
	}
}
