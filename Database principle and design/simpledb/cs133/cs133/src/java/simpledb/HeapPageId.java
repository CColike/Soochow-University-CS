package simpledb;

/** Unique identifier for HeapPage objects. */
public class HeapPageId implements PageId {
	private int m_tableId;
	private int m_pageNum;
    /**
     * Constructor. Create a page id structure for a specific page of a
     * specific table.
     *
     * @param tableId The table that is being referenced
     * @param pgNo The page number in that table.
     */
    public HeapPageId(int tableId, int pgNo) {
        m_tableId = tableId;
        m_pageNum = pgNo;
        // some code goes here
    }

    /** @return the table associated with this PageId */
    public int getTableId() {
        // some code goes here
        return m_tableId;
    }

    /**
     * @return the page number in the table getTableId() associated with
     *   this PageId
     */
    public int getPageNumber() {
        // some code goes here
        return m_pageNum;
    }

    /**
     * @return a hash code for this page, represented by the concatenation of
     *   the table number and the page number (needed if a PageId is used as a
     *   key in a hash table in the BufferPool, for example.). You may want to 
     *   parse the concatenation as a long (Long.parseLong()) before casting to int.
     * @see BufferPool
     */
    public int hashCode() {
        // some code goes here
        String toHash = "" + m_tableId + m_pageNum;
        return toHash.hashCode();
        // throw new UnsupportedOperationException("implement this");
    }

    /**
     * Compares one PageId to another.
     *
     * @param o The object to compare against (must be a PageId)
     * @return true if the objects are equal (e.g., page numbers and table
     *   ids are the same)
     */
    public boolean equals(Object o) {
        // some code goes here
    	if (o instanceof PageId){
	    	PageId pid = (PageId) o;
	    	return (this.getTableId() == pid.getTableId() && this.getPageNumber() == pid.getPageNumber());
    	}
    	else return false;
    }

    /**
     *  Return a representation of this object as an array of
     *  integers, for writing to disk.  Size of returned array must contain
     *  number of integers that corresponds to number of args to one of the
     *  constructors.
     */
    public int[] serialize() {
        int data[] = new int[2];

        data[0] = getTableId();
        data[1] = getPageNumber();

        return data;
    }

}
