#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x19600407, "module_layout" },
	{ 0x35903bb7, "kmalloc_caches" },
	{ 0x5a34a45c, "__kmalloc" },
	{ 0x4c4fef19, "kernel_stack" },
	{ 0xc2c1230, "generic_file_llseek" },
	{ 0xb9244fab, "__mark_inode_dirty" },
	{ 0xd6ee688f, "vmalloc" },
	{ 0x3f51ef89, "generic_fh_to_parent" },
	{ 0x67053080, "current_kernel_time" },
	{ 0x99ffb310, "is_bad_inode" },
	{ 0xe2a52be2, "test_set_page_writeback" },
	{ 0x20000329, "simple_strtoul" },
	{ 0xbe58b7e, "generic_file_aio_read" },
	{ 0x9f70cbb4, "remove_proc_entry" },
	{ 0xa45d5e06, "vfs_readlink" },
	{ 0x9e1bdc28, "init_timer_key" },
	{ 0x77d99252, "end_writeback" },
	{ 0xfcc00445, "mutex_unlock" },
	{ 0x5a4b4323, "generic_read_dir" },
	{ 0x999e8297, "vfree" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0x99362e82, "generic_file_aio_write" },
	{ 0x7d11c268, "jiffies" },
	{ 0xa6ce8c32, "truncate_setsize" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x64bd34bf, "end_page_writeback" },
	{ 0xe1bc7ede, "del_timer_sync" },
	{ 0xde0bdcff, "memset" },
	{ 0x11089ac7, "_ctype" },
	{ 0xff0082a0, "current_task" },
	{ 0x60b749c1, "__mutex_init" },
	{ 0x27e1a049, "printk" },
	{ 0x68a285b3, "kthread_stop" },
	{ 0x14d3c64e, "d_rehash" },
	{ 0x3f5028b0, "d_obtain_alias" },
	{ 0x2fa5a500, "memcmp" },
	{ 0xf5d247d4, "put_mtd_device" },
	{ 0x1a9533a9, "d_alloc_root" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0x7ec9bfbc, "strncpy" },
	{ 0xb4390f9a, "mcount" },
	{ 0x85abc85f, "strncmp" },
	{ 0xe8cd130a, "mutex_lock" },
	{ 0x9e66a26b, "setattr_copy" },
	{ 0x71205378, "add_timer" },
	{ 0xc080f70d, "unlock_page" },
	{ 0x9ca95a0e, "sort" },
	{ 0x61651be, "strcat" },
	{ 0xcc07af75, "strnlen" },
	{ 0xf0788f01, "generic_file_mmap" },
	{ 0x33c3f08f, "bdevname" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x1000e51, "schedule" },
	{ 0x35c2ba9e, "refrigerator" },
	{ 0x4b5814ef, "kmalloc_order_trace" },
	{ 0xe29f0adc, "do_sync_read" },
	{ 0x1b3d04b3, "unlock_new_inode" },
	{ 0xfd94ee2c, "kill_block_super" },
	{ 0xba021939, "create_proc_entry" },
	{ 0x9614fd39, "wake_up_process" },
	{ 0x1c011386, "get_mtd_device" },
	{ 0x22fadea5, "inode_change_ok" },
	{ 0xb557f9ed, "kmem_cache_alloc_trace" },
	{ 0x16ae6cc0, "register_filesystem" },
	{ 0xd2965f6f, "kthread_should_stop" },
	{ 0xab730ab4, "iput" },
	{ 0x37a0cba, "kfree" },
	{ 0x66c41d1a, "kthread_create" },
	{ 0x351f04b0, "do_sync_write" },
	{ 0x2d7b4e31, "generic_file_splice_write" },
	{ 0x236c8c64, "memcpy" },
	{ 0x47e72fa, "get_sb_bdev" },
	{ 0x8eb5a1ec, "put_page" },
	{ 0x74c134b9, "__sw_hweight32" },
	{ 0xeebe7997, "unregister_filesystem" },
	{ 0x72b289d4, "init_special_inode" },
	{ 0xb69efc8, "generic_file_splice_read" },
	{ 0x9f3797b0, "generic_fh_to_dentry" },
	{ 0xe39c7214, "grab_cache_page_write_begin" },
	{ 0x13095525, "param_ops_uint" },
	{ 0x12e4053d, "d_instantiate" },
	{ 0xb25f30fe, "iget_locked" },
	{ 0xe914e41e, "strcpy" },
	{ 0xe7118688, "truncate_inode_pages" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=mtd";


MODULE_INFO(srcversion, "7682AA1CFBE9CC3CEE87753");
