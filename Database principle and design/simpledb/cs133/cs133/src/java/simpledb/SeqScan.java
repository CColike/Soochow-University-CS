package simpledb;

import java.util.*;

/**
 * SeqScan is an implementation of a sequential scan access method that reads
 * each tuple of a table in no particular order (e.g., as they are laid out on
 * disk).
 */
public class SeqScan implements DbIterator {

    private static final long serialVersionUID = 1L;

    
    private TransactionId m_transId;
    private int m_tableId;
    private String m_tableAlias;
    private DbFile m_hFile;
    private DbFileIterator m_dbiterator;
    /**
     * Creates a sequential scan over the specified table as a part of the
     * specified transaction.
     * 
     * @param tid
     *            The transaction this scan is running as a part of.
     * @param tableid
     *            the table to scan.
     * @param tableAlias
     *            the alias of this table (needed by the parser); the returned
     *            tupleDesc should have fields with name tableAlias.fieldName
     *            (note: this class is not responsible for handling a case where
     *            tableAlias or fieldName are null. It shouldn't crash if they
     *            are, but the resulting name can be null.fieldName,
     *            tableAlias.null, or null.null).
     */
    public SeqScan(TransactionId tid, int tableid, String tableAlias) {
        // some code goes here
        m_transId = tid;
        m_tableAlias = tableAlias;
        m_tableId = tableid;
        m_hFile = Database.getCatalog().getDatabaseFile(tableid);
        m_dbiterator = m_hFile.iterator(m_transId);
    }

    /**
     * @return
     *       return the table name of the table the operator scans. This should
     *       be the actual name of the table in the catalog of the database
     * */
    public String getTableName() {
        // some code goes here
    	return Database.getCatalog().getTableName(m_tableId);
//        return null;
    }
    
    /**
     * @return Return the alias of the table this operator scans. 
     * */
    public String getAlias()
    {
        // some code goes here
        return m_tableAlias;
//        return null;
    }

    /**
     * Reset the tableid, and tableAlias of this operator.
     * @param tableid
     *            the table to scan.
     * @param tableAlias
     *            the alias of this table (needed by the parser); the returned
     *            tupleDesc should have fields with name tableAlias.fieldName
     *            (note: this class is not responsible for handling a case where
     *            tableAlias or fieldName are null. It shouldn't crash if they
     *            are, but the resulting name can be null.fieldName,
     *            tableAlias.null, or null.null).
     */
    public void reset(int tableid, String tableAlias) {
        m_tableId = tableid;
        m_tableAlias = tableAlias;
        // some code goes here
    }

    public SeqScan(TransactionId tid, int tableid) {
        this(tid, tableid, Database.getCatalog().getTableName(tableid));
    }

    public void open() throws DbException, TransactionAbortedException {
        // some code goes here
        m_dbiterator.open();
    }

    /**
     * Returns the TupleDesc with field names from the underlying HeapFile,
     * prefixed with the tableAlias string from the constructor. This prefix
     * becomes useful when joining tables containing a field(s) with the same
     * name. The alias and name should be separated with a "." character
     * (e.g., "alias.fieldName").
     * 
     * @return the TupleDesc with field names from the underlying HeapFile,
     *         prefixed with the tableAlias string from the constructor.
     */
    public TupleDesc getTupleDesc() {
        // some code goes here
    	TupleDesc origTupleDesc = Database.getCatalog().getTupleDesc(m_tableId);
    	int tdSize = origTupleDesc.numFields();
    	Type [] newTypes = new Type[tdSize];
    	String [] newFields = new String[tdSize];
    	for (int i = 0; i < tdSize; i++){
    		newTypes[i] = origTupleDesc.getFieldType(i);
    		newFields[i] = m_tableAlias + "." + origTupleDesc.getFieldName(i);
    	}
    	return new TupleDesc(newTypes, newFields);
//        return null;
    }

    public boolean hasNext() throws TransactionAbortedException, DbException {
        // some code goes here
        return m_dbiterator.hasNext();
//        return false;
    }

    public Tuple next() throws NoSuchElementException,
            TransactionAbortedException, DbException {
        // some code goes here
        return m_dbiterator.next();
//        return null;
    }

    public void close() {
        // some code goes here
        m_dbiterator.close();
    }

    public void rewind() throws DbException, NoSuchElementException,
            TransactionAbortedException {
    	m_dbiterator.rewind();
        // some code goes here
    }
}
