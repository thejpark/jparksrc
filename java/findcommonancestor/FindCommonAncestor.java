package findcommonancestor;

public interface FindCommonAncestor
{
    public String findCommmonAncestor(String[] commitHashes, String[][] parentHashes, String commitHash1, String commitHash2);
}
