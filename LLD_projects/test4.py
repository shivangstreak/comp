def complete(tiles):
    tile_counts = {}

    # Count the occurrences of each tile
    for tile in tiles:
        tile_counts[tile] = tile_counts.get(tile, 0) + 1

    # Count the number of pairs and triples
    pairs = 0
    triples = 0
    for key, count in tile_counts.items():
        print(f"{key} : {count}")
        triples += count//3
        if count % 3 == 2:
            pairs+=1

    return pairs == 1 and triples >= 1 and pairs*2 + triples * 3 == len(tiles)


tiles_1 = "773797439949499477339977777997394947947477993"
print(complete(tiles_1))