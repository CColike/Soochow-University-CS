fs/ext2/namei.c, line 141
static int ext2_mknod (struct inode * dir, struct dentry *dentry, umode_t mode, dev_t rdev)  
{  
    struct inode * inode;  
    int err;  
  
    err = dquot_initialize(dir);  
    if (err)  
        return err;  
  
    inode = ext2_new_inode (dir, mode, &dentry->d_name);  
    err = PTR_ERR(inode);  
    if (!IS_ERR(inode)) {  
        init_special_inode(inode, inode->i_mode, rdev);  
#ifdef CONFIG_EXT2_FS_XATTR  
        inode->i_op = &ext2_special_inode_operations;  
#endif  
        mark_inode_dirty(inode);  
        err = ext2_add_nondir(dentry, inode);  
    }  
    return err;  
} 


fs/ext2/namei.c, line 428 
struct inode_operations ext2_dir_inode_operations = { 
 .create = ext2_create, 
 .lookup = ext2_lookup, 
 .link = ext2_link, 
 .unlink = ext2_unlink, 
 .symlink = ext2_symlink, 
 .mkdir = ext2_mkdir, 
 .rmdir = ext2_rmdir, 
 .mknod = ext2_mknod, 
 .rename = ext2_rename, 
#ifdef CONFIG_EXT2_FS_XATTR 
 .setxattr = generic_setxattr, 
 .getxattr = generic_getxattr, 
 .listxattr = ext2_listxattr, 
 .removexattr = generic_removexattr, 
#endif 
 .setattr = ext2_setattr, 
 .permission = ext2_permission, 
};