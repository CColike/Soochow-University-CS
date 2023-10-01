package simpledb;

import simpledb.systemtest.SimpleDbTestBase;
import simpledb.systemtest.SystemTestUtil;

import java.io.File;
import java.util.*;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;
import junit.framework.JUnit4TestAdapter;

public class HeapFileReadTest extends SimpleDbTestBase {
    private HeapFile hf;
    private TransactionId tid;
    private TupleDesc td;

    /**
     * Set up initial resources for each unit test.
     */
    @Before
    public void setUp() throws Exception {
        hf = SystemTestUtil.createRandomHeapFile(2, 20, null, null);
        td = Utility.getTupleDesc(2);
        tid = new TransactionId();
    }

    @After
    public void tearDown() throws Exception {
        Database.getBufferPool().transactionComplete(tid);
    }

    /**
     * Unit test for HeapFile.getId()
     */
    @Test
    public void getId() throws Exception {
        int id = hf.getId();

        // NOTE(ghuo): the value could be anything. test determinism, at least.
        assertEquals(id, hf.getId());
        assertEquals(id, hf.getId());

        HeapFile other = SystemTestUtil.createRandomHeapFile(1, 1, null, null);
        assertTrue(id != other.getId());
    }

    /** Unit test for getFile() */
    @Test public void getFile() {

    	// just checking for implementation of this method
    	assertFalse(hf.getFile() == null);
    	
    }

    /**
     * Unit test for HeapFile.getTupleDesc()
     */
    @Test
    public void getTupleDesc() throws Exception {    	
        assertEquals(td, hf.getTupleDesc());        
    }
    /**
     * Unit test for HeapFile.numPages()
     */
    @Test
    public void numPages() throws Exception {
        assertEquals(1, hf.numPages());
        // assertEquals(1, empty.numPages());
    }

    /**
     * Unit test for HeapFile.readPage()
     */
    @Test
    public void readPage() throws Exception {
        HeapPageId pid = new HeapPageId(hf.getId(), 0);
        HeapPage page = (HeapPage) hf.readPage(pid);

        // NOTE(ghuo): we try not to dig too deeply into the Page API here; we
        // rely on HeapPageTest for that. perform some basic checks.
        assertEquals(484, page.getNumEmptySlots());
        assertTrue(page.isSlotUsed(1));
        assertFalse(page.isSlotUsed(20));
    }

    @Test
    public void testIteratorBasic() throws Exception {
        HeapFile smallFile = SystemTestUtil.createRandomHeapFile(2, 3, null,
                null);

        DbFileIterator it = smallFile.iterator(tid);
        
        // Not open yet
        //assertFalse(it.hasNext());
        try {
            it.hasNext();
            fail("expected exception");
        } catch (IllegalStateException e) {
        }
        try {
            it.next();
            fail("expected exception");
        } catch (IllegalStateException e2) {
        }

        it.open();
        int count = 0;
        while (it.hasNext()) {
            assertNotNull(it.next());
            count += 1;
        }
        assertEquals(3, count);
        it.close();
    }

    @Test
    public void testIteratorClose() throws Exception {
        // make more than 1 page. Previous closed iterator would start fetching
        // from page 1.
        HeapFile twoPageFile = SystemTestUtil.createRandomHeapFile(2, 520,
                null, null);

        DbFileIterator it = twoPageFile.iterator(tid);
        it.open();
        assertTrue(it.hasNext());
        it.close();
        try {
            it.next();
            fail("expected exception");
        } catch (IllegalStateException e) {
        }
        // close twice is harmless
        it.close();
    }
    
    @Test
    public void testIteratorEmptyPages() throws Exception {
    	int numTuples = 992; // fills one page
    	
    	// make files with two and three full pages
        ArrayList<ArrayList<Integer>> tuples = new ArrayList<ArrayList<Integer>>();
    	File twoFullPages = SystemTestUtil.createRandomHeapFileUnopened(1, 2*numTuples, 1000, null, tuples);
    	File threeFullPages = SystemTestUtil.createRandomHeapFileUnopened(1, 3*numTuples, 1000, null, tuples);

    	// make a blank page for inserting 
    	byte[] blankData = HeapPage.createEmptyPageData();
    	
    	// make a three-page HeapFile: full, full, blank
    	java.io.RandomAccessFile raf = new java.io.RandomAccessFile(twoFullPages,"rw");
    	raf.seek(2*BufferPool.getPageSize());
    	raf.write(blankData);
    	raf.close();
    	HeapFile hf = Utility.openHeapFile(1, twoFullPages);
    	assertEquals(3,hf.numPages()); // HeapFile should recognize that there are three pages
    	
    	// iterator should get all tuples without failing
    	DbFileIterator it = hf.iterator(tid);
    	int count = 0;
    	it.open();
        while (it.hasNext()) {
            assertNotNull(it.next());
            count += 1;
        }
        assertEquals(2*numTuples, count);
        it.close();
        
        // now try the iterator with a file as: blank, full, blank
        raf = new java.io.RandomAccessFile(threeFullPages,"rw");
    	raf.write(blankData);
    	raf.seek(2*BufferPool.getPageSize());
    	raf.write(blankData);
    	raf.close();
    	HeapFile hf2 = Utility.openHeapFile(1, threeFullPages);
    	assertEquals(3,hf2.numPages()); // HeapFile should recognize that there are three pages
    	
    	// iterator should get all tuples without failing
    	it = hf2.iterator(tid);
    	count = 0;
    	it.open();
        while (it.hasNext()) {
            assertNotNull(it.next());
            count += 1;
        }
        assertEquals(numTuples, count);
        it.close();
        
    }
    
    /**
     * JUnit suite target
     */
    public static junit.framework.Test suite() {
        return new JUnit4TestAdapter(HeapFileReadTest.class);
    }
}
