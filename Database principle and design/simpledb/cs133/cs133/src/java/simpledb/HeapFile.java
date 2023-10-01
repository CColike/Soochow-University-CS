package simpledb;

import java.io.*;
import java.util.*;

/**
 * HeapFile is an implementation of a DbFile that stores a collection of tuples
 * in no particular order. Tuples are stored on pages, each of which is a fixed
 * size, and the file is simply a collection of those pages. HeapFile works
 * closely with HeapPage. The format of HeapPages is described in the HeapPage
 * constructor.
 * 
 * @see simpledb.HeapPage#HeapPage
 * @author Sam Madden
 */
public class HeapFile implements DbFile {

    private int id;
    private File file;
    private TupleDesc td;
    /**
     * Constructs a heap file backed by the specified file.
     * 
     * @param f
     *            the file that stores the on-disk backing store for this heap
     *            file.
     */
    public HeapFile(File f, TupleDesc td) {
        this.file = f;
        this.id = f.getAbsoluteFile().hashCode();
        this.td = td;
        // some code goes here
    }

    /**
     * Returns the File backing this HeapFile on disk.
     * 
     * @return the File backing this HeapFile on disk.
     */
    public File getFile() {
        // some code goes here
        return this.file;
//        return null;
    }

    /**
     * Returns an ID uniquely identifying this HeapFile. Implementation note:
     * you will need to generate this tableid somewhere to ensure that each
     * HeapFile has a "unique id," and that you always return the same value for
     * a particular HeapFile. We suggest hashing the absolute file name of the
     * file underlying the heapfile, i.e. f.getAbsoluteFile().hashCode().
     * 
     * @return an ID uniquely identifying this HeapFile.
     */
    public int getId() {
        // some code goes here
    	return this.id;
//        throw new UnsupportedOperationException("implement this");
    }

    /**
     * Returns the TupleDesc of the table stored in this DbFile.
     * 
     * @return TupleDesc of this DbFile.
     */
    public TupleDesc getTupleDesc() {
        // some code goes here
        return this.td;
//        throw new UnsupportedOperationException("implement this");
    }

    // see DbFile.java for javadocs
    public Page readPage(PageId pid) {
        // some code goes here
		HeapPageId hpid = (HeapPageId) pid; // cast to HeapPageId
		BufferedInputStream bis = null; // The stream to read file from
		try {
			bis = new BufferedInputStream(new FileInputStream(file));
			byte pageBuf[] = new byte[BufferPool.getPageSize()];

			// Total number of bytes in the pages to skip.
			long bytesToSkip = hpid.getPageNumber() * BufferPool.getPageSize();

			// Attempt to skip these bytes in the file.
			long bytesSkipped = bis.skip(bytesToSkip);

			if (bytesSkipped != bytesToSkip) { // Verify we skipped correct # of
												// bytes.
				throw new IllegalArgumentException(
						"Unable to seek to correct place in heapfile");
			}

			// Read the page into pageBuf.
			int bytesRead = bis.read(pageBuf, 0, BufferPool.getPageSize());
			if (bytesRead == -1) {
				throw new IllegalArgumentException("Read past end of table.");
			}
			if (bytesRead < BufferPool.getPageSize()) {
				throw new IllegalArgumentException("Unable to read "
						+ BufferPool.getPageSize() + " bytes from heapfile.");
			}
			Debug.log(1, "HeapFile.readPage: read page %d", hpid.getPageNumber());
			return new HeapPage(hpid, pageBuf);
		} catch (IOException ioe) {
			throw new RuntimeException(ioe);
		} finally { // Close the file on success or error
			try {
				if (bis != null) {
					bis.close();
				}
			} catch (IOException ioe) {
				// Ignore failures closing the file
			}
		}
//        return null;
    }

    // see DbFile.java for javadocs
    public void writePage(Page page) throws IOException {
        // some code goes here
        // not necessary for lab1
    }

    /**
     * Returns the number of pages in this HeapFile.
     */
    public int numPages() {
        // some code goes here
    	 return (int) Math.ceil(this.file.length()/BufferPool.getPageSize());
//        return 0;
    }

    // see DbFile.java for javadocs
    public ArrayList<Page> insertTuple(TransactionId tid, Tuple t)
            throws DbException, IOException, TransactionAbortedException {
        // some code goes here
        return null;
        // not necessary for lab1
    }

    // see DbFile.java for javadocs
    public ArrayList<Page> deleteTuple(TransactionId tid, Tuple t) throws DbException,
            TransactionAbortedException {
        // some code goes here
        return null;
        // not necessary for lab1
    }

    // see DbFile.java for javadocs
    public DbFileIterator iterator(TransactionId tid) {
        // some code goes here
        return new HeapFileIterator(this, tid);
//        return null;
    }
    class HeapFileIterator implements DbFileIterator {

    	private Tuple next = null;
        Iterator<Tuple> it = null;
        int curpgno = Integer.MAX_VALUE;

        TransactionId tid;
        HeapFile hf;

        public HeapFileIterator(HeapFile hf, TransactionId tid) {
            this.hf = hf;
            this.tid = tid;
        }

        public void open() throws DbException, TransactionAbortedException {
            curpgno = -1;
        }
        
    	public boolean hasNext() throws TransactionAbortedException, DbException  {
    		if(curpgno==Integer.MAX_VALUE)throw new IllegalStateException();
            if (next == null) next = readNext();
            return next != null;
        }

        public Tuple next() throws DbException, TransactionAbortedException,
                NoSuchElementException {
            if (next == null) {
                next = readNext();
//                return null;
                if (next == null) throw new IllegalStateException();
            }

            Tuple result = next;
            next = null;
            return result;
        }

        Tuple readNext() throws TransactionAbortedException, DbException {
            if (it != null && !it.hasNext())
                it = null;

            while (it == null && curpgno < hf.numPages() - 1) {
                curpgno++;
                HeapPageId curpid = new HeapPageId(hf.getId(), curpgno);
                HeapPage curp = (HeapPage) Database.getBufferPool().getPage(tid,
                        curpid, Permissions.READ_ONLY);
                it = curp.iterator();
                if (!it.hasNext())
                    it = null;
            }

            if (it == null)
                return null;
            return it.next();
        }

        public void rewind() throws DbException, TransactionAbortedException {
            close();
            open();
        }

        public void close() {
        	next = null;
            it = null;
            curpgno = Integer.MAX_VALUE;
        }
    }
}

