export function parsePPM(content: string): { width: number, height: number, data: Uint8ClampedArray } | null {
  // Remove comments (everything from # to end of line)
  const cleanContent = content.replace(/#.*/g, '');
  
  // Split by any whitespace (spaces, tabs, newlines) and remove empty strings
  const tokens = cleanContent.trim().split(/\s+/).filter(t => t.length > 0);
  
  if (tokens.length < 4) return null; // Needs P3, width, height, maxColor

  const header = tokens[0];
  if (header !== 'P3') return null;

  const width = parseInt(tokens[1]!, 10);
  const height = parseInt(tokens[2]!, 10);
  const maxColor = parseInt(tokens[3]!, 10);

  if (isNaN(width) || isNaN(height) || isNaN(maxColor)) return null;

  // PPM P3 is RGB, so 3 values per pixel. Canvas ImageData is RGBA (4 values).
  const data = new Uint8ClampedArray(width * height * 4);
  let pixelIndex = 0;
  let tokenIndex = 4;

  while (tokenIndex < tokens.length && pixelIndex < data.length) {
      // Need 3 tokens for R, G, B
      if (tokenIndex + 2 >= tokens.length) break;

      const rStr = tokens[tokenIndex++]!;
      const gStr = tokens[tokenIndex++]!;
      const bStr = tokens[tokenIndex++]!;

      const rVal = parseInt(rStr, 10);
      const gVal = parseInt(gStr, 10);
      const bVal = parseInt(bStr, 10);

      // Normalize color if maxColor is not 255 (though usually it is)
      const r = Math.floor((rVal / maxColor) * 255);
      const g = Math.floor((gVal / maxColor) * 255);
      const b = Math.floor((bVal / maxColor) * 255);

      data[pixelIndex++] = r;
      data[pixelIndex++] = g;
      data[pixelIndex++] = b;
      data[pixelIndex++] = 255; // Alpha is always 255 (opaque)
  }

  return { width, height, data };
}

export function toPPM(width: number, height: number, data: Uint8ClampedArray): string {
  let ppm = 'P3\n';
  ppm += `${width} ${height}\n`;
  ppm += '255\n';

  for (let i = 0; i < data.length; i += 4) {
      const r = data[i];
      const g = data[i + 1];
      const b = data[i + 2];
      // Ignore alpha for PPM
      ppm += `${r} ${g} ${b} `;
      // Add newline every row for readability (optional but good)
      if (((i / 4) + 1) % width === 0) {
          ppm += '\n';
      }
  }
  return ppm;
}