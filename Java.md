* ListIterator<E> in ArrayList<E>
```java
    /**
     * An optimized version of AbstractList.ListItr
     */
    private class ListItr extends Itr implements ListIterator<E> {
        ListItr(int index) {
            super();
            cursor = index;
        }

        public boolean hasPrevious() {
            return cursor != 0;
        }

        public int nextIndex() {
            return cursor;
        }

        public int previousIndex() {
            return cursor - 1;
        }

        @SuppressWarnings("unchecked")
        public E previous() {
            if (modCount != expectedModCount)
                throw new ConcurrentModificationException();
            int i = cursor - 1;
            if (i < 0)
                throw new NoSuchElementException();
            Object[] elementData = ArrayList.this.elementData;
            if (i >= elementData.length)
                throw new ConcurrentModificationException();
            cursor = i;
            return (E) elementData[lastRet = i];
        }

        public void set(E e) {
            if (lastRet < 0)
                throw new IllegalStateException();
            if (modCount != expectedModCount)
                throw new ConcurrentModificationException();

            try {
                ArrayList.this.set(lastRet, e);
            } catch (IndexOutOfBoundsException ex) {
                throw new ConcurrentModificationException();
            }
        }

        public void add(E e) {
            if (modCount != expectedModCount)
                throw new ConcurrentModificationException();

            try {
                int i = cursor;
                ArrayList.this.add(i, e);
                cursor = i + 1;
                lastRet = -1;
                expectedModCount = modCount;
                limit++;
            } catch (IndexOutOfBoundsException ex) {
                throw new ConcurrentModificationException();
            }
        }
    }
```

* Java IO
    * Reader
        * BufferedReader
        * InputStreamReader
            * FileReader

    * InputStream
        * FilterInputStream
            * InflaterInputStream
                * GZIPInputStream
            * DataInputStream o- DataInput
            * BufferedInputStream
        * FileInputStream

# 語法:
    * 如果想在一個java檔裡寫多個class都在最外層，最多就只能留一個public class。