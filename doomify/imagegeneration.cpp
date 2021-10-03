#include "imagegeneration.h"

GeneratedImage GenerateImage(QImage image, ImageSchema properties){
    GeneratedImage result;
    result.schema = properties;
    result.image = properties.usingImageDimensions ? QImage(image.width(),image.height(),QImage::Format_ARGB32) : QImage(properties.width,properties.height,QImage::Format_ARGB32);

    QColor background_color = result.schema.backgroundColor;
    background_color.setAlpha(result.schema.transparent ? 0 : 255);
    result.image.fill(background_color);

    QImage reference_image = image.scaled(QSize(result.image.width(),result.image.height()),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
    QPainter painter;
    painter.begin(&result.image);
    for (int h = 0; h < reference_image.height(); ++h) {
        for (int w = 0; w < reference_image.width(); ++w) {
            QColor draw_color = GetClosestColor(reference_image.pixelColor(w,h),result.schema.palette.colors);
            draw_color.setAlpha(reference_image.pixelColor(w,h).alpha());
            painter.setPen(draw_color);
            painter.drawPoint(w,h);
        }
    }
    painter.end();

    return result;
}

QColor GetClosestColor(QColor original, std::vector<QColor> colors){
    QColor closest_color;
    int closest_color_offset = 0;

    for (auto i = colors.begin(); i != colors.end(); i++)
    {
        // Grab the difference in values across each colors' RGB channel
        int i_offset = 0;
        i_offset += abs(original.red() - (*i).red());
        i_offset += abs(original.green() - (*i).green());
        i_offset += abs(original.blue() - (*i).blue());

        if(i == colors.begin()){
            closest_color = *i;
            closest_color_offset = i_offset;
            continue;
        }

        // If the total difference is smaller than the current lowest color's, then it acts as the closest approximation so far to the original color
        if (i_offset < closest_color_offset)
        {
            closest_color = *i;
            closest_color_offset = i_offset;
        }
    }

    return closest_color;
}