//
//     ____    _                        __     _      _____
//    / ___\  /_\     /\/\    /\ /\    /__\   /_\     \_   \
//    \ \    //_\\   /    \  / / \ \  / \//  //_\\     / /\/
//  /\_\ \  /  _  \ / /\/\ \ \ \_/ / / _  \ /  _  \ /\/ /_
//  \____/  \_/ \_/ \/    \/  \___/  \/ \_/ \_/ \_/ \____/
//
//	Copyright Samurai development team and other contributors
//
//	http://www.samurai-framework.com
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in
//	all copies or substantial portions of the Software.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//	THE SOFTWARE.
//

#import "Samurai_Core.h"
#import "Samurai_UIConfig.h"

#if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)

#import "Samurai_Tree.h"

#pragma mark -

#undef	INVALID_VALUE
#define	INVALID_VALUE			(HUGE_VALF)

#undef	NORMALIZE_VALUE
#define NORMALIZE_VALUE( __x )	((__x == INVALID_VALUE) ? 0.0f : __x)

#pragma mark -

#if __has_feature(objc_arc)

#undef	outlet
#define	outlet( type, name ) \
		property (nonatomic, unsafe_unretained) type name

#undef	def_outlet
#define	def_outlet( type, name, ... ) \
		synthesize name = _##name;

#else

#undef	outlet
#define	outlet( type, name ) \
		property (nonatomic, assign) type name

#undef	def_outlet
#define	def_outlet( type, name, ... ) \
		synthesize name = _##name;

#endif

#pragma mark -

@class SamuraiDomNode;
@class SamuraiDocument;
@class SamuraiRenderObject;
@class SamuraiRenderStyle;

@interface NSObject(Renderer)

@prop_strong( SamuraiRenderObject *, renderer );

+ (id)createInstanceWithRenderer:(SamuraiRenderObject *)renderer;	// override point
+ (id)createInstanceWithRenderer:(SamuraiRenderObject *)renderer identifier:(NSString *)identifier;	// override point

- (void)prepareForRendering;							// override point

- (CGSize)computeSizeBySize:(CGSize)size;				// override point
- (CGSize)computeSizeByWidth:(CGFloat)width;			// override point
- (CGSize)computeSizeByHeight:(CGFloat)height;			// override point

- (void)applyFrame:(CGRect)frame;						// override point

@end

#pragma mark -

@interface SamuraiRenderObject : SamuraiTreeNode

@prop_strong( NSNumber *,				id );
@prop_unsafe( SamuraiDomNode *,			dom );
@prop_strong( SamuraiRenderStyle *,		style );

@prop_assign( NSInteger,				index );
@prop_assign( CGRect,					frame );
@prop_assign( CGPoint,					offset );

@prop_assign( UIEdgeInsets,				inset );
@prop_assign( UIEdgeInsets,				margin );
@prop_assign( UIEdgeInsets,				padding );
@prop_assign( UIEdgeInsets,				border );

@prop_strong( UIView *,					view );
@prop_strong( Class,					viewClass );

@prop_readonly( SamuraiRenderObject *,	root );
@prop_unsafe( SamuraiRenderObject *,	parent );
@prop_unsafe( SamuraiRenderObject *,	prev );
@prop_unsafe( SamuraiRenderObject *,	next );

+ (instancetype)renderObject;
+ (instancetype)renderObjectWithDom:(SamuraiDomNode *)dom andStyle:(SamuraiRenderStyle *)style;

+ (Class)defaultViewClass;										// override point

- (void)bindOutletsTo:(NSObject *)container;
- (void)unbindOutletsFrom:(NSObject *)container;

- (SamuraiRenderObject *)queryById:(NSString *)domId;
- (SamuraiRenderObject *)queryByDom:(SamuraiDomNode *)domNode;

- (SamuraiRenderObject *)prevObject;
- (SamuraiRenderObject *)nextObject;
- (SamuraiRenderObject *)findObjectWithTabIndex:(NSInteger)tabIndex exclude:(SamuraiRenderObject *)sourceObject;

- (CGRect)zerolizeFrame;
- (CGFloat)computeWidth:(CGFloat)height;
- (CGFloat)computeHeight:(CGFloat)width;
- (CGRect)computeFrame:(CGSize)bound;							// override point
- (CGRect)computeFrame:(CGSize)bound origin:(CGPoint)origin;	// override point

- (UIView *)createViewWithIdentifier:(NSString *)identifier;	// override point

- (void)bindView:(UIView *)view;	// override point
- (void)unbindView;					// override point

- (void)relayout;					// override point
- (void)restyle;					// override point
- (void)rechain;					// override point

@end

#endif	// #if (TARGET_OS_IPHONE || TARGET_IPHONE_SIMULATOR)
