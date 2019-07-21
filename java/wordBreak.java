import java.util.HashMap;
import java.util.Map;
import java.lang.Character;
import java.lang.Integer;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;


class Node {
    Node() {}
    public Map<Character, Node> ms = new HashMap<Character, Node>();
    public boolean complete = false;
}

class Trie {
    public Node root = new Node();
    public void add(String s)
    {
        int len = s.length();
        Node n = root;
        int i = 0;
        while (i < len)
        {
            Character key = Character.valueOf(s.charAt(i));
            if (n.ms.containsKey(key))
            {
                n = n.ms.get(key);
                ++i;
            }
            else
            {
                break;
            }
        }

        while (i < len)
        {
            Node val = new Node();
            Character key = Character.valueOf(s.charAt(i));

            n.ms.put(key, val);
            // System.out.println("add : " + key.toString());
            n = val;
            ++i;
        }
        n.complete = true;
        // System.out.println("done for : " + s);
    }
}

class Solution {
    public List<String> wordBreak(String s, List<String> wordDict) {
        List<String> l = new ArrayList<String>();
        Trie trie = new Trie();
        for (String e : wordDict)
        {
            trie.add(e);
        }
        Map<Integer, List<String>> mm = new HashMap<>();

        foo(trie, s, 0, l, mm);

        for (Map.Entry e : mm.entrySet()) //
            System.out.println(e.getKey() + " : " + e.getValue());

        return l;
    }

    void foo(Trie trie, String s, int idx, List<String> r,
            Map<Integer, List<String>> mm)
    {
        if (idx == s.length())
        {
            r.add(new String());
            return;
        }

        if (mm.containsKey(Integer.valueOf(idx)))
        {
            r.addAll(mm.get(idx));
            return;
        }

        Node n = trie.root;
        int i = 0;
        Character key = Character.valueOf(s.charAt(idx + i));
        StringBuffer tt = new StringBuffer();
        while (n.ms.containsKey(key))
        {
            n = n.ms.get(key);
            tt.append(key);
            // System.out.println("> " + tt.toString());

            if (n.complete)
            {
                List<String> rr = new ArrayList<>();

                foo(trie, s, idx + i + 1, rr, mm);
                for (String e: rr)
                {
                    if (e.length() == 0)
                    {
                        r.add(tt.toString());
                    }
                    else
                    {
                        r.add(tt.toString() + " " + e);
                    }
                }
            }
            ++i;
            if (idx + i == s.length())
                break;
            key = Character.valueOf(s.charAt(idx + i));
            // System.out.println(">> " + key.toString());
        }

        mm.put(Integer.valueOf(idx), r);
        System.out.println("> " + String.valueOf(idx));
        for (String e : r)
            System.out.println(e);

    }

    public static void main(String args[])
    {
        Solution sol = new Solution();

        String[] sa = {"cat", "cats", "and", "sand", "dog"};
        List<String> wordDict = new ArrayList<>(Arrays.asList(sa));
        List<String> l = sol.wordBreak("catsanddog", wordDict);

        for (String e: l)
        {
            System.out.println(e);
        }

        System.out.println("done");

    }
}
