#ifndef H_RPMVERCMP
#define	H_RPMVERCMP

#ifdef __cplusplus
extern "C" {
#endif

/** \ingroup rpmtrans
 * Segmented string compare for version or release strings.
 *
 * @param a		1st string
 * @param b		2nd string
 * @return		+1 if a is "newer", 0 if equal, -1 if b is "newer"
 */
int rpmvercmp(const char * a, const char * b);

#ifdef __cplusplus
}
#endif

#endif	/* H_RPMVERCMP */
