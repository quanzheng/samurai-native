//
//  MovieCell.m
//  movie
//
//  Created by QFish on 4/10/15.
//  Copyright (c) 2015 Geek Zoo Studio. All rights reserved.
//

#import "MovieListCell.h"
#import "Samurai.h"
#import "Model.h"
#import "UIColor+Movie.h"

@interface MovieListCell()
@property (nonatomic, strong) UILabel * critics_label;
@end

@implementation MovieListCell

- (void)unserialize:(id)obj
{
    [super unserialize:obj];

    if ( obj )
    {
        NSInteger score = [obj[@"critics"] integerValue];

        self.critics_label.cssStyle.color = makeColor( [UIColor mv_colorWithScore:score] );
        self.critics_label.text = [NSString stringWithFormat:@"critics %@%%", obj[@"critics"]];

		[self.critics_label restyle];
    }
}

@end
