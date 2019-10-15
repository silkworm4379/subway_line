package Struct;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

public class Vexs {
    public static int vnumber=0;
    public static String line_result=null;
    
    public line [] x=null;
    public ArrayList<String>  stationmap=null;
    public Map<String, Integer> mapline =null;
    
    public ArrayList<String>  station=null;
    public Map<String, Integer> map =null;       //数据采用的哈希表结构

    public Vexs(){

    }

    public Vexs(String [] station){
        int num=0;
        num=station.length;
        this.station=new ArrayList<String>(num);
        for(int i=0;i<num;i++){
            this.station.set(i,station[i]);
        }

    }

}
