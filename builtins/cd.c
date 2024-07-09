#include <string.h>

static void    error_message_for_invalid_change_repository(void)
{
    ft_putstr_fd("Minishell: cd: \n", 2);
    ft_putstr_fd("/invalid/path: No such file or directory", 2);
}

static int  get_directory(char **old_pwd, char *actual_dir, t_list *env_var, char *var_to_edit)
{
    if (old_pwd)
    {
        // je fais une copie de old_pwd
        *old_pwd = strdup(*old_pwd);
        if (!old_pwd)
        {
            // si la copie echoue
            ft_putstr_fd("Minishell: cd: cannot load OLDPWD", 2);
            return (-1);
        }
        // pour obtenir le repertoire actuel
        if (!getcwd(actual_dir, BUFFER_SIZE))
        {
            ft_putstr_fd("Minishell: cd: cannod load OLDPWD", 2);
            if (old_pwd)
                free(*old_pwd);
            return (-1);
        }
        // Mettre Ã  jour la variable d'environnement var_to_edit avec actual_dir
        // permet que les variables d'environnement soit a jour
        // edit var c'est une fonction que tu dois creer 
        // elle recherche la variable d'environnement et l'ajoute a une liste chainee et met a jour sa 
        // valeur si elle n'existe pas. elle ajoute la nouvelle variable a ala liste.
        if (!edit_var(env_var, var_to_edit, actual_dir))
        {
            if (old_pwd)
                free(*old_pwd);
            return (-1);
        }
    }
    return (1);
}

static int  cd_old_pwd(t_list **env_var)
{
    char *old_pwd;
    char current_repository[BUFFER_SIZE];

    old_pwd = get_envp(*env_var, "OLDPWD");
    if (!old_pwd)
    {
        ft_putstr_fd("Minishell: cd: OLDPWD not set\n", 2);
        return (1);
    }
    // recupere le repertoire actuel et met a jour oldpwd
    if (get_directory(&old_pwd, current_repository, env_var, "OLDPWD") == 0)
            return (1);
    // changement de repertoire , si echoue message d'erreur et return (1);
    if (chdir(old_pwd) == -1)
    {
        error_message_for_invalid_change_repository();
        free(old_pwd);
        return (1);
    }
    // afficher le nouveau repertoire
    ft_putstr(old_pwd); 
    free(old_pwd);
    // mise a jour de pwd
     if (get_directory(NULL, current_repository, env_var, "PWD") == 0)
            return (1);
    return (0);
}


static int cd_go_to_home(t_list **env_var)
{
    char *home;

    // on recuperer la variable HOME dans l'environnement
    // ici faudra que tu adaptes les arguments d'entree par rapport a ta fonction
    home = get_envp(*env_var, "HOME");
    // si on a unset le HOME , on print un message d'erreur
    if (!home)
    {
        ft_putstr_fd("Minishell: cd: HOME not set\n", 2);
        return (1);
    }
    // mise a jour du repertoire , et si cela n'a pas marcher 
    // on print un message d'erreur et on return 1
    else if(chdir(home) == -1)
    {
        error_message_for_invalid_change_repository();
        return (1);
    }
    return (0);
}

int ft_cd(int argc, char **argv, t_list **env_var)
{
    // Il sert a stocker le repertoire actuel 
    char current_repository[BUFFER_SIZE];

    if (argc == 2)
    {
        // Dans bash si il y a un '-' on doit retourner l'ancier directory
        if (ft_strcmp(argv[1], "-") == 0)
            return (cd_old_pwd(env_var));
        // on appelle c'est fonction pour obtenir l'ancien repertoire
        // si la fonction echoue elle return 0 (par exemple si le OLDPWD n'est pas defini)
        if (get_directory(NULL, current_repository, env_var, "OLDPWD") == 0)
            return (1);
        // chdir permet de changer de repertoire
        // si il echoue il return (-1) et un message d'erreur
        if (chdir(argv[1]) == -1)
        {
            error_message_for_invalid_change_repository();
            return (1);
        }
        // on appelle c'est fonction pour obtenir repertoire actuel
        // si la fonction echoue elle return 0 (par exemple si le PWD n'est pas defini)
        if (get_directory(NULL, current_repository, env_var, "PWD") == 0)
            return (1);
    }
    else if (argc > 2)
    {
        ft_putstr_fd("Minishell: cd: too many arguments\n", 2);
        return (1);
    }
    else if (argc == 1)
        return (cd_go_to_home(env_var));
    return (0);
}
