package client;
import Struct.AMGraph;
import Struct.Vexs;
import Struct.line;

import java.io.*;
import java.util.*;

public class Launch {
    public static void main(String[] args) {
        Read("data1.txt","data2.txt");
    }


    //按照字符读文件
    public static void Read(String fileName,String fileName2) {
        Scanner input=new Scanner(System.in);
        File file = new File(fileName);
//        Reader reader = null;
        Vexs v=new Vexs();
        AMGraph g=new AMGraph();
        try {
            System.out.println("以字符为单位读取文件内容，一次读多个字节：");
            // 一次读多个字符
//            char[] tempchars = new char[50];
//            int charread = 0;
//            reader = new InputStreamReader(new FileInputStream(fileName));

//            StringBuilder result = new StringBuilder();
            BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(file), "UTF-8"));
            String s=null;
            ArrayList<String> arraylist=new ArrayList<String>();
            v.map = new HashMap<String,Integer>();
            while ((s = br.readLine()) != null&&!s.equals("")) {//使用readLine方法，一次读一行
                String[] splitted = s.split(" ");
                arraylist.add(splitted[0]);
                arraylist.add(splitted[1]);
            }
            v.station = new ArrayList<>(new LinkedHashSet<>(arraylist));
            for(int i=0;i<v.station.size();i++){
                v.map.put(v.station.get(i),i);
            }
            br.close();
            //读入转站信息
            File file1=new File(fileName2);
            v.mapline=new HashMap<String,Integer>();
            StringBuilder result2 = new StringBuilder();
            BufferedReader br2 = new BufferedReader(new InputStreamReader(new FileInputStream(file1), "UTF-8"));
            v.x=new line[500];
            ArrayList<String> arraylist2=new ArrayList<String>();
            while ((s = br2.readLine()) != null&&!s.equals("")) {//使用readLine方法，一次读一行
                String[] splitted = s.split(" ");
                v.x[Vexs.vnumber]=new line();
                v.x[Vexs.vnumber].l=new ArrayList<String>();
                for(int j=0;j<splitted.length;j++){
                    if(j==0){
                        arraylist2.add(splitted[j]);
                    }
                    else{
                        v.x[Vexs.vnumber].l.add(splitted[j]);
                    }


                }
                Vexs.vnumber++;
            }
            v.stationmap = new ArrayList<>(new LinkedHashSet<>(arraylist2));
            for(int i=0;i<v.stationmap.size();i++){
                v.mapline.put(v.stationmap.get(i),i);
            }
            br2.close();
            

            g.distance=new int[v.station.size()][v.station.size()];
            g.matrix_dist=new int[v.station.size()][v.station.size()];
            g.matrix_path=new int[v.station.size()][v.station.size()];
            for(int i=0;i<arraylist.size();i=i+2){
                int a=v.map.get(arraylist.get(i));
                int b=v.map.get(arraylist.get(i+1));
                g.distance[a][b]=1;
                g.distance[b][a]=1;
            }
        } catch (Exception e1) {
            e1.printStackTrace();
        }

        System.out.println("请输入两个站点的名称（站点之间加空格）：");
        String a=input.next();
        String b=input.next();

        floyd(g,v,a,b);
        ArrayList<Integer> result=getPath(g,v,a,b);
        String before=new String(v.station.get(result.get(result.size()-1)));
        String after=new String(v.station.get(result.get(result.size()-1)));
        String now=new String(v.station.get(result.get(result.size()-1)));
        int needchange=0;
        for(int i=result.size()-1;i>=0;i--){
            if(i>1&&i<result.size()-1) after=v.station.get(result.get(i-1));
            now=v.station.get(result.get(i));
            if(isChange(g, v, before,after)&&i>1&&i<result.size()-1){
                needchange=1;
            }

            if(needchange==1&&i<result.size()-1){
                if(has(g, v, v.station.get(result.get(i-1)), v.station.get(result.get(i-2)))){
                    System.out.println("转站"+Vexs.line_result);
                }
            }

            before=v.station.get(result.get(i));
            System.out.print(v.station.get(result.get(i))+" ");
            needchange=0;


        }
    }

    public static boolean isChange(AMGraph g,Vexs v,String a,String b){
        if(has(g, v, a, b)){
            return false;
        }
        
        return true;
    }

    public static boolean has(AMGraph g,Vexs v,String a,String b){
        for(int i=0;i<v.x[v.mapline.get(a)].l.size();i++){
            for(int j=0;j<v.x[v.mapline.get(b)].l.size();j++){
                if(v.x[v.mapline.get(a)].l.get(i).equals(v.x[v.mapline.get(b)].l.get(j))){
                    Vexs.line_result=v.x[v.mapline.get(a)].l.get(i);
                    return true;
                }
            }
            
        }
        
        return false;
    }


    public static void floyd(AMGraph g,Vexs v,String a,String b){

        for (int i=0;i< v.station.size();i++)
            for (int j = 0; j < v.station.size(); j++)
            {
                g.matrix_dist[i][j] = g.distance[i][j];//初始化距离矩阵
                g.matrix_path[i][j] = i;//初始化路径矩阵
            }
        int temp=0;
        //三重循环
        for (int k = 0; k < v.station.size(); k++) {
            for (int i = 0; i < v.station.size(); i++) {
                for (int j = 0; j < v.station.size(); j++) {
                    if (g.matrix_dist[i][k] != 0 && g.matrix_dist[k][j] != 0)
                        if ((temp = g.matrix_dist[i][k] + g.matrix_dist[k][j]) < g.matrix_dist[i][j] || g.matrix_dist[i][j] == 0) {
                            //更新距离和路径
                            g.matrix_dist[i][j] = temp;
                            g.matrix_path[i][j] = g.matrix_path[k][j];
                        }
                }
            }
        }

    }

//返回路径
    public static ArrayList<Integer> getPath(AMGraph g,Vexs v,String a,String b){
        int k;
        k = v.map.get(b);
        ArrayList<Integer> res=null;
        if (g.matrix_dist[v.map.get(a)][v.map.get(b)] == 0){
            return res;
        }
        res=new ArrayList<Integer>();
        while (k != v.map.get(a)){
            res.add(k);
            k = g.matrix_path[v.map.get(a)][k];
        }
        res.add(k);

        return res;
    }


}
