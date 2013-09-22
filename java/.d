diff --git a/.DS_Store b/.DS_Store
index eac77fc..a459010 100644
Binary files a/.DS_Store and b/.DS_Store differ
diff --git a/java/flatten/MyFlattenTree.java b/java/flatten/MyFlattenTree.java
index fb16284..b1894b9 100644
--- a/java/flatten/MyFlattenTree.java
+++ b/java/flatten/MyFlattenTree.java
@@ -8,27 +8,41 @@ import java.util.ArrayList;
 public class MyFlattenTree<T> implements FlattenTree<T>
 {
 
-    class myfunc implements Function<T, List<T>>
+    static final class myfunc<T> implements Function<T, List<T>>
     {
+        public myfunc(MyFlattenTree<T> t)
+        {
+            mft = t;
+        }
+        
         public List<T> apply(T p) 
         {
             List<T> r = new ArrayList<T>();
             r.add(p);
             return r;
         }
+
+        private MyFlattenTree<T> mft;
+        
     }
 
-    class myfunc2 implements Function<Triple<Tree<T>>, List<T>>
+    static final class myfunc2<T> implements Function<Triple<Tree<T>>, List<T>>
     {
+        public myfunc2(MyFlattenTree<T> t) 
+        {
+            mft = t;
+        }
+        
         public List<T> apply(Triple<Tree<T>> p) 
         {
             List<T> r = new ArrayList<T>();
 
-            r.addAll(MyFlattenTree.this.flattenInOrder(p.left()));
-            r.addAll(MyFlattenTree.this.flattenInOrder(p.middle()));
-            r.addAll(MyFlattenTree.this.flattenInOrder(p.right()));
+            r.addAll(mft.flattenInOrder(p.left()));
+            r.addAll(mft.flattenInOrder(p.middle()));
+            r.addAll(mft.flattenInOrder(p.right()));
             return r;
         }
+        private MyFlattenTree<T> mft;
     }
 
     public List<T> flattenInOrder(Tree<T> tree) 
@@ -39,11 +53,11 @@ public class MyFlattenTree<T> implements FlattenTree<T>
         Either<T, Triple<Tree<T>>> n =  tree.get();
 
         if (n.isLeft()) {
-            List<T> l = n.ifLeft(this.new myfunc());
+            List<T> l = n.ifLeft(new myfunc<T>(this));
             return l;
         } else {
 
-            List<T> l = n.ifRight(this.new myfunc2());
+            List<T> l = n.ifRight(new myfunc2<T>(this));
             return l;
         }
 
