import java.io.*;
import java.util.*;

public class CountRadixSort {

    public static void main(String[] args) throws IOException{
        
        //String PATH = "";
        int i,j,k,SIZE=20000000;
        File dataFile = null;
        BufferedWriter writer = null;
        BufferedReader reader=null;
        File sortFile=null;

        
        Random random = new Random();
        dataFile = new File("data.txt");
        writer = new BufferedWriter(new FileWriter(dataFile));
        

        for(i=0;i<SIZE;i++){
            writer.write(random.nextInt(999999)+1+"");
            writer.newLine();
        }
        writer.close();
        

        sortFile = new File("sort.txt");
        dataFile = new File("data.txt");
        writer = new BufferedWriter(new FileWriter(sortFile));
        reader = new BufferedReader(new FileReader(dataFile));
        int[] usArray = new int[200000000]; 
        int[] sArray = new int[200000000];

        ////////////////////////
        long t=System.nanoTime();
        int num;
        int[] countArray = new int[1000000];

        for(i=0;i<1000000;i++){
            countArray[i]=0;
        }
        for(i=0;i<SIZE;i++){
            num=Integer.parseInt(reader.readLine());
            usArray[i]=num;
            countArray[num]++;
        }
        //
        for(i=0;i<1000000;i++){
            for(j=0;j<countArray[i];j++){
                writer.write(i+"");
                writer.newLine();
            }
        }
        //
        k=0;
        for(i=0;i<1000000;i++){
            for(j=0;j<countArray[i];j++){
                sArray[k++]=i;
            }
        }
        t=System.nanoTime()-t;
        ///////////////////////
        System.out.println("Count Sort:"+t/1000000+" ms");
        reader.close();
        writer.close();

        int[] digArray=new int[10];
        int div=1;
        k=0;

        t=System.nanoTime();
        while(k<6){
            for(i=0;i<10;i++){
                digArray[i]=0;
            }
            for(i=0;i<SIZE;i++){
                digArray[(usArray[i]/div)%10]++;
            }
            for(i=1;i<10;i++){
                digArray[i]+=digArray[i-1];
            }
            for(i=SIZE-1;i>=0;i--){
                sArray[--digArray[(usArray[i]/div)%10]]=usArray[i];
            }
            for(i=0;i<SIZE;i++){
                usArray[i]=sArray[i];
            }
            div*=10;
            k++;
        }
        t=System.nanoTime()-t;
        System.out.println("Radix Sort:"+t/1000000+" ms");
    }
}