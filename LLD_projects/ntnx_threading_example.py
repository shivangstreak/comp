import threading
threads = []
for cluster in self.dbservers_on_cluster:
    dbservers = self.dbservers_on_cluster[cluster]
    if cluster == self.primary_dbserver.nx_cluster_id:
        thread = threading.Thread(name=cluster, target=self.restore_native_backups_on_secondaries_on_primary_cluster,
                                  args=(dbservers, disk_info,))
    else:
        thread = threading.Thread(name=cluster, target=self.replicate_native_snapshot_to_cluster_and_restore_replicas,
                                  args=(self.primary_snapshot_id, cluster, dbservers, disk_info,))
    thread.start()
    threads.append(thread)
for thread in threads:
    thread.join()