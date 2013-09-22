package findcommonancestor;


public class MyFindCommonAncestor implements FindCommonAncestor
{

    public String findCommmonAncestor(String[] commitHashes,
            String[][] parentHashes, String commitHash1, String commitHash2)
    {
        int idx1, idx2;

        idx1 = find (commitHashes, commitHash1);
        idx2 = find (commitHashes, commitHash2);

        int min = Min (idx1, idx2);
        int max = Max (idx1, idx2);
        
        int idx = findMinParent(min, max, commitHashes, parentHashes);
        
        return commitHashes[idx];
    }

    private int findMinParent(int idx, int max, String[] ch, String[][] ph)
    {
        if (idx >= max) // which is end condition?
            return idx;
        
        int min = ch.length; // which is max value?

        for (int i = 0; i < ph[idx].length; ++i) {
            String e = ph[idx][i];
            int tidx = find(ch, e);
            int tidx2 = findMinParent(tidx, max, ch, ph);
            min = Min (min, tidx2);
        }
        
        return min;
    }
    
    private int find (String[] ch, String ch1)
    {
        for (int i = 0; i < ch.length; i++) {
            if (ch[i].equals(ch1))
                         return i;
        }
        return -1;
    }

    private int Max (int a, int b)
    {
        if (a > b)
            return a;
        else return b;
    }
    
    private int Min (int a, int b)
    {
        if (a > b)
            return b;
        else return a;
    }
    
}

