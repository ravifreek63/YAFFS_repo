/*
 * YAFFS: Yet Another Flash File System. A NAND-flash specific file system.
 *
 * Copyright (C) 2002-2011 Aleph One Ltd.
 *   for Toby Churchill Ltd and Brightstar Engineering
 *
 * Created by Charles Manning <charles@aleph1.co.uk>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include "yaffs_packedtags2.h"
#include "yportenv.h"
#include "yaffs_trace.h"
#include "yaffs_guts.h"
#include "stdbool.h"

extern bool set_extra_tags(enum EXTRA_TAGS_NAME etn, struct extra_information_tags *eit_struct, unsigned int value);
extern int get_extra_tags(enum EXTRA_TAGS_NAME etn, struct extra_information_tags *eit_struct);

/* This code packs a set of extended tags into a binary structure for
 * NAND storage
 */

/* Some of the information is "extra" stuff which can be packed in to
 * speed scanning
 * This is defined by having the EXTRA_HEADER_INFO_FLAG set.
 */

/* Extra flags applied to chunk_id */

#define EXTRA_HEADER_INFO_FLAG	0x80000000
#define EXTRA_SHRINK_FLAG	0x40000000
#define EXTRA_SHADOWS_FLAG	0x20000000
#define EXTRA_SPARE_FLAGS	0x10000000

#define ALL_EXTRA_FLAGS		0xf0000000

/* Also, the top 4 bits of the object Id are set to the object type. */
#define EXTRA_OBJECT_TYPE_SHIFT (28)
#define EXTRA_OBJECT_TYPE_MASK  ((0x0f) << EXTRA_OBJECT_TYPE_SHIFT)

static void yaffs_dump_packed_tags2_tags_only(
				const struct yaffs_packed_tags2_tags_only *ptt)
{
	
	yaffs_trace(YAFFS_TRACE_MTD,
		"packed tags obj %d chunk %d byte %d seq %d transaction %u",
		ptt->obj_id, ptt->chunk_id, ptt->n_bytes, ptt->seq_number, ptt->transaction_id);

	/*printf("packed tags obj %d chunk %d byte %d seq %d transaction %u",
		ptt->obj_id, ptt->chunk_id, ptt->n_bytes, ptt->seq_number, ptt->transaction_id);
	printf ("DONE yaffs_dump_packed_tags2_tags_only\n");*/

}

static void yaffs_dump_packed_tags2(const struct yaffs_packed_tags2 *pt)
{
	yaffs_dump_packed_tags2_tags_only(&pt->t);
}

static void yaffs_dump_tags2(const struct yaffs_ext_tags *t)
{
	//printf("IN yaffs_dump_tags2\n");
	yaffs_trace(YAFFS_TRACE_MTD,
		"ext.tags eccres %d blkbad %d chused %d obj %d chunk%d byte %d del %d ser %d seq %d transaction id %u",
		t->ecc_result, t->block_bad, t->chunk_used, t->obj_id,
		t->chunk_id, t->n_bytes, t->is_deleted, t->serial_number,
		t->seq_number, t->transaction_id);

	/*printf(YAFFS_TRACE_MTD, "ext.tags eccres %d blkbad %d chused %d obj %d chunk%d byte %d del %d ser %d seq %d transaction id %u",
		t->ecc_result, t->block_bad, t->chunk_used, t->obj_id,
		t->chunk_id, t->n_bytes, t->is_deleted, t->serial_number,
		t->seq_number, t->transaction_id);*/
        //printf("DONE yaffs_dump_tags2\n");


}

void yaffs_pack_tags2_tags_only(struct yaffs_packed_tags2_tags_only *ptt, const struct yaffs_ext_tags *t)
{
	ptt->chunk_id = t->chunk_id;
	ptt->seq_number = t->seq_number;
	ptt->n_bytes = t->n_bytes;
	ptt->obj_id = t->obj_id;

/*
 * For copying the transaction id from the yaffs_ext_tags structure to the packed tags structure
 */
       ptt->transaction_id = t->transaction_id;


/*
* Chunk ID = 0 means the chunk is a object header.
* The first four bits of chunk id of an object header are used to state binary information about chunk_id, extra_is_shrink, extra_shadows, extra spare flags.

* Also, the top 4 bits of the object Id of an object header are set to the object type. 
*/
/*enum EXTRA_TAGS_NAME etn;
int extra_available = get_extra_tags(etn.EXTRA_AVAILABLE, &(t->eit_struct));
int extra_is_shrink = get_extra_tags(etn.EXTRA_IS_SHRINK, &(t->eit_struct));
if (extra_available < 0)
	{
		printf ("Error: yaffs_pack_tags2_tags_only: get_extra_tags returns negative value\n");
	}*/
	if (t->chunk_id == 0 && t->extra_available)
	{
		/* Store the extra header info instead */
		/* We save the parent object in the chunk_id */

		ptt->chunk_id = EXTRA_HEADER_INFO_FLAG | t->extra_parent_id;
		if (t->extra_is_shrink)
		//if (t->
			ptt->chunk_id |= EXTRA_SHRINK_FLAG;
		if (t->extra_shadows)
			ptt->chunk_id |= EXTRA_SHADOWS_FLAG;

		ptt->obj_id &= ~EXTRA_OBJECT_TYPE_MASK;
		ptt->obj_id |= (t->extra_obj_type << EXTRA_OBJECT_TYPE_SHIFT);

		if (t->extra_obj_type == YAFFS_OBJECT_TYPE_HARDLINK)
			ptt->n_bytes = t->extra_equiv_id;
		else if (t->extra_obj_type == YAFFS_OBJECT_TYPE_FILE)
			ptt->n_bytes = t->extra_length;
		else
			ptt->n_bytes = 0;
	}

	yaffs_dump_packed_tags2_tags_only(ptt);
	yaffs_dump_tags2(t);
	//printf("DONE yaffs_pack_tags2_tags_only\n");
}

void yaffs_pack_tags2(struct yaffs_packed_tags2 *pt,
		      const struct yaffs_ext_tags *t, int tags_ecc)
{
	yaffs_pack_tags2_tags_only(&pt->t, t);

	if (tags_ecc)
		yaffs_ecc_calc_other((unsigned char *)&pt->t,
				    sizeof(struct yaffs_packed_tags2_tags_only),
				    &pt->ecc);
}

void yaffs_unpack_tags2_tags_only(struct yaffs_ext_tags *t,
				  struct yaffs_packed_tags2_tags_only *ptt)
{
	memset(t, 0, sizeof(struct yaffs_ext_tags));

	if (ptt->seq_number == 0xffffffff)
		return;

	t->block_bad = 0;
	t->chunk_used = 1;
	t->obj_id = ptt->obj_id;
	t->chunk_id = ptt->chunk_id;
	t->n_bytes = ptt->n_bytes;
	t->is_deleted = 0;
	t->serial_number = 0;
	t->seq_number = ptt->seq_number;

/*
 *  Reading the transaction id we have already stored
 */
      // printf("Reading transaction %u\n", ptt->transaction_id);
       t->transaction_id = ptt->transaction_id;
     
 
	/* Do extra header info stuff */
	if (ptt->chunk_id & EXTRA_HEADER_INFO_FLAG) {
		t->chunk_id = 0;
		t->n_bytes = 0;

/*enum EXTRA_TAGS_NAME etn;
bool ret_extra_available = set_extra_tags(etn.EXTRA_AVAILABLE, &(t->eit_struct), 1);
if (!(ret_extra_available))
	{
		printf ("Error :yaffs_unpack_tags2_tags_only:set_extra_tags : returns false");
	}*/
	// Earlier Code
	        t->extra_available = 1;
		t->extra_parent_id = ptt->chunk_id & (~(ALL_EXTRA_FLAGS));
		t->extra_is_shrink = ptt->chunk_id & EXTRA_SHRINK_FLAG ? 1 : 0;
		t->extra_shadows = ptt->chunk_id & EXTRA_SHADOWS_FLAG ? 1 : 0;
		t->extra_obj_type = ptt->obj_id >> EXTRA_OBJECT_TYPE_SHIFT;
		t->obj_id &= ~EXTRA_OBJECT_TYPE_MASK;

		if (t->extra_obj_type == YAFFS_OBJECT_TYPE_HARDLINK)
			t->extra_equiv_id = ptt->n_bytes;
		else
			t->extra_length = ptt->n_bytes;
	}
	yaffs_dump_packed_tags2_tags_only(ptt);
	yaffs_dump_tags2(t);
}

void yaffs_unpack_tags2(struct yaffs_ext_tags *t, struct yaffs_packed_tags2 *pt,
			int tags_ecc)
{
	//printf("In yaffs_unpack_tags2\n");
	enum yaffs_ecc_result ecc_result = YAFFS_ECC_RESULT_NO_ERROR;

	if (pt->t.seq_number != 0xffffffff && tags_ecc) {
		/* Chunk is in use and we need to do ECC */

		struct yaffs_ecc_other ecc;
		int result;
		yaffs_ecc_calc_other((unsigned char *)&pt->t,
				sizeof(struct yaffs_packed_tags2_tags_only),
				&ecc);
		result =
		    yaffs_ecc_correct_other((unsigned char *)&pt->t,
				sizeof(struct yaffs_packed_tags2_tags_only),
				&pt->ecc, &ecc);
		switch (result) {
		case 0:
			ecc_result = YAFFS_ECC_RESULT_NO_ERROR;
			break;
		case 1:
			ecc_result = YAFFS_ECC_RESULT_FIXED;
			break;
		case -1:
			ecc_result = YAFFS_ECC_RESULT_UNFIXED;
			break;
		default:
			ecc_result = YAFFS_ECC_RESULT_UNKNOWN;
		}
	}
	yaffs_unpack_tags2_tags_only(t, &pt->t);

	t->ecc_result = ecc_result;

	yaffs_dump_packed_tags2(pt);
	yaffs_dump_tags2(t);
}
