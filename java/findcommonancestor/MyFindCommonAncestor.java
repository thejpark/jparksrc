package findcommonancestor;
import java.lang.Math;
import java.util.*;


public class MyFindCommonAncestor implements FindCommonAncestor
{

    public String findCommmonAncestor(String[] commitHashes,
            String[][] parentHashes, String commitHash1, String commitHash2)
    {
	Set<String> s1 = findParent(commitHash1, commitHashes, parentHashes);
	Set<String> s2 = findParent(commitHash2, commitHashes, parentHashes);
	s1.retainAll(s2);
	return findMin(s1, commitHashes);
    }

    String findMin(Set<String> s, String[] commitHashes)
    {
	int min = commitHashes.length;
	for (String x: s) {
	    int k = find(commitHashes, x);
	    min = Math.min(min, k);
	}
	return commitHashes[min];
    }

    Set<String> findParent(String a, String[] ch, String[][] ph)
    {
	int k = find(ch, a);
	Set<String> r = new HashSet<String>();

	if (null == ph[k])
	    return r;

	for (String s: ph[k]) {
		r.add(s);
		Set<String> x = findParent(s, ch, ph);
		r.addAll(x);
	}

	return r;
    }

    private int find (String[] ch, String ch1)
    {
        for (int i = 0; i < ch.length; i++) {
            if (ch[i].equals(ch1))
                         return i;
        }
        return -1;
    }
}
